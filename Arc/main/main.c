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
static inline void progressBar(int i, int total);


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
  
  // Parallel thread section.
  #pragma omp parallel default (none), firstprivate(thread,photon), shared(totalData,exo)
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
        progressBar(i*omp_get_num_threads(),exo.nPhot);
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
static inline void progressBar(int i, int total){
  
  // Width of progress bar.
  int width = 58;
  
  // Only update 100 times.
  if (i % ((total/(100*omp_get_num_threads())) + 1) != 0){
    return;
  }
  
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