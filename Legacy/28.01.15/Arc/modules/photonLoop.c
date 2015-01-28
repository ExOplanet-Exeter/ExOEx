/*==============================================================                                      
----------------------------------------------------------------
██████╗ ██╗  ██╗ ██████╗ ████████╗ ██████╗ ███╗   ██╗
██╔══██╗██║  ██║██╔═══██╗╚══██╔══╝██╔═══██╗████╗  ██║
██████╔╝███████║██║   ██║   ██║   ██║   ██║██╔██╗ ██║
██╔═══╝ ██╔══██║██║   ██║   ██║   ██║   ██║██║╚██╗██║
██║     ██║  ██║╚██████╔╝   ██║   ╚██████╔╝██║ ╚████║
╚═╝     ╚═╝  ╚═╝ ╚═════╝    ╚═╝    ╚═════╝ ╚═╝  ╚═══╝
                      ██╗      ██████╗  ██████╗ ██████╗  ██████╗
                      ██║     ██╔═══██╗██╔═══██╗██╔══██╗██╔════╝
                      ██║     ██║   ██║██║   ██║██████╔╝██║     
                      ██║     ██║   ██║██║   ██║██╔═══╝ ██║     
                      ███████╗╚██████╔╝╚██████╔╝██║██╗  ╚██████╗
                      ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝   ╚═════╝
----------------------------------------------------------------
          The photonLoop is the core module of ExOEx.
    This function performs the huge majority of calculations
involved with calculating the path of photons as the are emitted 
    from a stellar surface and irradiated onto an exoplanet.
 The photon's path as it interacts with the various mediums of 
              the exoplanet is then simulated.
 Finally the emission vector as the photon leaves the exoplanet 
                     is then calculated. 
----------------------------------------------------------------                   
==============================================================*/


//== INCLUDES ==================================================                   
//-- SYSTEM HEADERS --------------------------------------------
// Allows use of math functions such as sine/cosine etc.
// Will most likely be moved to 'global.h' in the future.
#include <math.h>

//-- LOCAL HEADERS ---------------------------------------------
#include "../globals/global.h"


//== FUNCTION IN PROGRESS ======================================                   
// When functions are working as intended move to header please.


//== PHOTON LOOP FUNCTION ======================================
void photonLoop(Particle photon[], Planet exo){
  
//-- ENTRY -----------------------------------------------------
  // Debug printing.                                                                 
  if (DEBUG){
    printf(ACYAN "Photon Loop Running:\n" ARESET);
  }

//-- PHOTON LOOP -----------------------------------------------

// THIS IS FOR TESTING! REMOVE WHEN DONE PLEASE!
  for (int k=0; k<exo.nPhot; k++){
    photon[k].alpha=2.0;
  }

  return;
}
