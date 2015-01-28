/*==============================================================
----------------------------------------------------------------
                     ╔════════════════════╗
                     ║ ExOplanet - Exeter ║            
                     ╚════════════════════╝                     
----------------------------------------------------------------

████████████╗              █████████╗   ████████████╗
████████████║             ███████████╗  ████████████║
████╔═══════╝            █████╔══█████╗ ████╔═══════╝
████║         ███╗  ███╗ ████╔╝   ████║ ████║         ███╗  ███╗
████████╗     ███║  ███║ ████║    ████║ ████████╗     ███║  ███║
████████║      ███╗███╔╝ ████║    ████║ ████████║      ███╗███╔╝
████╔═══╝       █████╔╝  ████║    ████║ ████╔═══╝       █████╔╝
████║          ███╔███╗  █████╗  █████║ ████║          ███╔███╗
████████████╗ ███╔╝ ███╗  ███████████╔╝ ████████████╗ ███╔╝ ███╗
████████████║ ███║  ███║   █████████╔╝  ████████████║ ███║  ███║
╚═══════════╝ ╚══╝  ╚══╝   ╚════════╝   ╚═══════════╝ ╚══╝  ╚══╝

----------------------------------------------------------------
          ███╗   ███╗ █████╗ ██╗███╗   ██╗    ██████╗
          ████╗ ████║██╔══██╗██║████╗  ██║   ██╔════╝
          ██╔████╔██║███████║██║██╔██╗ ██║   ██║     
          ██║╚██╔╝██║██╔══██║██║██║╚██╗██║   ██║     
          ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║██╗╚██████╗
          ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚═╝ ╚═════╝
----------------------------------------------------------------
        This program simulates polarised light observed 
              from an irradiated extrasolar planet
----------------------------------------------------------------
==============================================================*/


//== INCLUDES ==================================================
//-- SYSTEM HEADERS --------------------------------------------
// These will be found in system library files and do not need
// to be included locally. They use <> containers.
#include <stdlib.h>

//-- LOCAL HEADERS ---------------------------------------------
// These local header files must be placed within the working
// directory. They use "" containers.
#include "globals/global.h"
#include "modules/module.h"


//== FUNCTION IN PROGRESS ======================================
// When functions are working as intended move to header please

void titlePrint(){
  printf(ARED
	 "\n"
	 "╔════════════════════════════════════════════════════"
	 "═════════╗\n"
	 "║                                                    "
	 "         ║\n"
	 "║           ███████╗██╗  ██╗ ██████╗ ███████╗██╗  ██╗"
	 "         ║\n"
	 "║           ██╔════╝╚██╗██╔╝██╔═══██╗██╔════╝╚██╗██╔╝"
	 "         ║\n"
	 "║           █████╗   ╚███╔╝ ██║   ██║█████╗   ╚███╔╝ "
	 "         ║\n"
	 "║           ██╔══╝   ██╔██╗ ██║   ██║██╔══╝   ██╔██╗ "
	 "         ║\n"
	 "║           ███████╗██╔╝ ██╗╚██████╔╝███████╗██╔╝ ██╗"
	 "         ║\n"
	 "║           ╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝"
	 "         ║\n"
         "║                                                    "
         "         ║\n"
         "╚════════════════════════════════════════════════════"
         "═════════╝\n\n"
	 ARESET);

  return;
}



//== MAIN FUNCTION =============================================
int main(){

//-- ENTRY -----------------------------------------------------
  // Print title
  titlePrint();

  // Debug printing. ACOLOUR and ARESET change terminal colour.
  if (DEBUG)
    printf(ACYAN "ExOEx Running:\n" ARESET);


//-- INITIALISATION --------------------------------------------
  srand(777);


//-- DECLERATIONS ----------------------------------------------
  // Create exoplanet with default parameters (altered by .cfg)
  Planet exo = {DEFAULT_NPHOT, DEFAULT_NLAYERS, DEFAULT_KAPPA};
  // Create an array of nPhot photons.
  //  Particle photon[exo.nPhot] = 0;


//-- CORE MODULES ----------------------------------------------
  // Config file reading stage
  // Pass exo to input for modifying by .cfg file
  exo = input(exo);
  // Create an array of nPhot photons.
  // Done after input func encase exo.nPhot is changed.
  Particle photon[exo.nPhot];
  // Main computation loop.

  // THIS WAS FOR TESTING __ REMOVE WHEN DONE!
  for (int k=0; k<22; k++){
    photon[k].alpha=1.0;
    printf(AYELLOW "%lf\n" ARESET, photon[k].alpha);
  }

  // Main computational simulation loop.
  photonLoop(photon, exo);

  // AGAIN THIS IS FOR TESTING, REMOVE WHEN DONE!
  for (int k=0; k<22; k++){
    printf(ARED "%lf\n" ARESET, photon[k].alpha);
  }

  // Data output stage.
  //  output(photon[exo.nPhot]);

//-- EXIT AND CLEANUP ------------------------------------------
  // Resets console colour. This shouldn't be needed though!
  if (DEBUG == 0)
    printf("Resetting console colour.\n");

  if (DEBUG)
    printf(AGREEN "ExOEx Complete.\n" ARESET);
  return 0;
}
