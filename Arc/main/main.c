/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
 __________                  ______     __________
|          |                /      \   |          |  
|  ________| ___    ____   /   __   \  |  ________| ____    ____
|       |    \   \  /   / |   /  \   | |       |    \   \  /   /
|     __|     \   \/   /  |  |    |  | |     __|     \   \/   / 
|    |         \      /   |  |    |  | |    |         \      / 
|    |_____    /  __  \   |   \__/   | |    |_____    /  __  \
|          |  /  /  \  \   \        /  |          |  /  /  \  \ 
|__________| /__/    \__\   \______/   |__________| /__/    \__\
├──────────────────────────────────────────────────────────────┤
                  _ __ ___   __ _(_)_ __    ___ 
                 | '_ ` _ \ / _` | | '_ \  / __|
                 | | | | | | (_| | | | | || (__
                 |_| |_| |_|\__,_|_|_| |_(_)___|           
├──────────────────────────────────────────────────────────────┤
  This program simulates polarised light as it scatted through
  the atmosphere of an extrasolar planet before being observed.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
// External libraries <>.
// Allows for parallelisation settings.
#include <omp.h>
// Local libraries "".
#include "../globals/global.h"
#include "../globals/utilities.h"
#include "../modules/modules.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
static inline void progressBar(int,int,int,time_t);
void printTimeTaken(time_t);


//── MAIN ─────────────────────────────────────────────────────┤
int main(){
  
  // -- Entry
  printTitle();
  if (DEBUG){
    printStart("ExOEx");
    FILE *file;  
    file = fopen(outputPath "position.dat","w");
   
    if (file == NULL)
      printErr("Could not open position.dat"); 

    fclose(file);
  }
  
  // -- Declerations
  // g_variable is for global use, p_variable is for private
  // string use.
  ThreadInfo thread = {0};
  Datasystem totalData = {0};
  Planet exo = {0};
  Particle photon = {0};

  // -- Initialisation
  exo.nLayers  = readInt("config.cfg","nLayers");
  exo.nPhot    = readInt("config.cfg","nPhot");
  
  // -- Memory allocation
  exo.scatType = malloc(exo.nLayers * sizeof *exo.scatType);
  exo.kappa    = malloc(exo.nLayers * sizeof *exo.kappa);
  exo.albedo   = malloc(exo.nLayers * sizeof *exo.albedo);
  exo.radius   = malloc(exo.nLayers * sizeof *exo.radius);
  
  // -- Core modules
  input(&exo,&photon);
  
  if (DEBUG)
    printStart("Photon Loop");
    
  time_t start = time(NULL);
  
  // Parallel thread section.
  #pragma omp parallel default (none), firstprivate(thread,photon), shared(totalData,exo,start)
  {  
    // Indervidual thread initialisation.
    #pragma omp critical
    {
      photonLoop(&exo,&photon);
    }

    thread.id = omp_get_thread_num();    

    if (thread.id == 0)
      printf(ABLUE "Number of threads running: %i\n" ARESET,omp_get_num_threads());

    // Parallel thread for loop.
    #pragma omp for
    for (int i=0; i<exo.nPhot; i++){
      if (thread.id == 0){
        progressBar(i*omp_get_num_threads(),exo.nPhot,i,start);
      }
      
      photonLoop(&exo,&photon);
      extraction(&photon,&thread);
      
      thread.nLoop++;
    }
    
    // Thread convergence.
    #pragma omp critical
    {
      reduction(&thread,&totalData);

      printf(ABLUE "Thread #%i ran %i/%i (%lf%%)\n" ARESET,
        thread.id,thread.nLoop,exo.nPhot,(100.0*thread.nLoop)/exo.nPhot);
    }
  }
  
  printTimeTaken(start);
  
  if (DEBUG)
    printEnd("Photon Loop");
    
  output(&totalData);
  
  // -- Clean up
  free(exo.scatType);
  free(exo.kappa);
  free(exo.albedo);
  free(exo.radius);
  
  // -- Exit
  if (DEBUG)
    printEnd("ExOEx");
  
  return 0;
}


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤
static inline void progressBar(int i,int total,int j,time_t start){
  
  // Width of progress bar.
  int width = 50;
  
  // Only update 100 times.
  if (i % ((total/((total/100000)*omp_get_num_threads())) + 1) != 0){
    return;
  }
  
  // --- Time testing
  if (i >= 100000){
    double elapsed = (double)(time(NULL) - start);
    
    double timePerPhot = elapsed/j;
    
    double endTime = (1.0-((1.0*j)/total))*timePerPhot*total;
    
    if (endTime <= 120){
      printf(AYELLOW "ETC: %.2fs" ARESET,endTime);
    }
    else if ((endTime > 120) && (endTime <= 7200)){
      int min = endTime / 60;
      printf(AYELLOW "ETC: %im" ARESET,min); 
    }
    else {
      int hr = endTime / 3600;
      printf(AYELLOW "ETC: %ihr" ARESET,hr);
    }
    
  }
  // --- End of time testing
  
  // Fraction completed.
  double frac = i/(1.0*total);
  int c = frac * width;
  
  // Print percentage complete.
  printf(AYELLOW "%3d%% [" ARESET, (int)(frac*100));
  
  // Print progress bar.
  for (int i=0; i<c; i++){
    printf(AYELLOW "=" ARESET);
  }
  for (int i=c; i<width; i++){
    printf(" ");
  }
  
  // ANSI consol control codes to return to previous line and
  // clean it.
  printf(AYELLOW "]\n\033[F\033[J" ARESET);
  
  return;
}

void printTimeTaken(time_t start){
  
  double timeTaken = (double)(time(NULL) - start);
  
  if (timeTaken <= 120){
    printf(AYELLOW "Time taken: %.2fs\n" ARESET,timeTaken);
  }
  else if ((timeTaken > 120) && (timeTaken <= 7200)){
    int min = timeTaken / 60;
    printf(AYELLOW "Time taken: %im\n" ARESET,min); 
  }
  else {
    int hr = timeTaken / 3600;
    printf(AYELLOW "Time taken: %ihr\n" ARESET,hr);
  }
  
  return;
}