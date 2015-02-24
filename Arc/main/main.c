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
  #pragma omp parallel firstprivate(thread)
  {  
    // Indervidual thread initialisation.
    #pragma omp critical
    {
      srand(clock());
    }

    thread.id = omp_get_thread_num();    

    if (thread.id == 0)
      printf(ABLUE "Number of threads running: %i\n" ARESET,omp_get_num_threads());

    // Parallel thread for loop.
    #pragma omp for
    for (int i=0; i<exo.nPhot; i++){
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
