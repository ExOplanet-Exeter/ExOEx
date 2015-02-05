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
    This program simulates polarised light observed from an
    irradiated extrasolar planet.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "globals/global.h"
#include "globals/utilities.h"
#include "modules/headers/module.h"


//── MAIN ─────────────────────────────────────────────────────┤
int main(){
  
  // Entry
  printTitle();
  if (DEBUG)
    printf(ACYAN "ExOEx Running:\n" ARESET);

  // Initialisation
  srand(2434);

  // Declerations
  Planet exo;
  int nLayers = readInt("config.cfg","nLayers");

  // Memory allocation
  exo.lType   = malloc(nLayers * sizeof *exo.lType);
  exo.lKappa  = malloc(nLayers * sizeof *exo.lKappa);
  exo.lAlbedo = malloc(nLayers * sizeof *exo.lAlbedo);
  exo.lRadius = malloc(nLayers * sizeof *exo.lRadius);
  
  // Core modules
  
  // Clean up
  free(exo.lType);
  free(exo.lKappa);
  free(exo.lAlbedo);
  free(exo.lRadius);

  // Exit
  if (DEBUG)
    printf(AGREEN "ExOEx Complete.\n\n" ARESET);
    
  return 0;
}