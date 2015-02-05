/*
  --- \ / /-\ --- \ /
  --   x  | | --   x
  --- / \ \_/ --- / \

  ExOplanet - Exeter

  This programme simulates polarised light observed from an 
  irradiated extrasolar planet
*/

//================================================== INCLUDES ==
#include <stdio.h>                                              // <> Brackets are normal include headers
#include <stdlib.h>
#include <unistd.h>

#include "global.h"                                             // "" Indicate local headers
#include "modules.h"


//============================================= MAIN FUNCTION ==
int main(){
  if (DEBUG)                                                    // Debug printing
    printf(ACYAN "\nStage: Main\n" ARESET);                     // ACYAN and ARESET are terminal colouring
  
  // Initialisation
  srand(777);                                                   // Seed for random number gen
  
  // Declerations
  Planet exo = {DEFAULT_NPHOT, DEFAULT_NLAYERS, DEFAULT_RADIUS};// Set exoplanet up with default parameters
  Particle photon[exo.nPhot];                                   // Maximum number of photons corresponds

  // Core functions
  exo = input(exo);                                             // Config reading stage

  if (DEBUG)
    printf(ACYAN "\nStage: Photon Loop\n" ARESET);

  for (int n=0; n<exo.nPhot; n++) {                             // Photon loop stage
    photon[n] = photonLoop(exo,n);
  }

  output(photon,exo);                                           // Output stage

  return 0;
}
