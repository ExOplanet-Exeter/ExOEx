/*==============================================================
----------------------------------------------------------------
             88
             88                         ,d
             88                         88
8b,dPPYba,   88,dPPYba,    ,adPPYba,  MM88MMM  ,adPPYba,
88P'    "8a  88P'    "8a  a8"     "8a   88    a8"     "8a
88       d8  88       88  8b       d8   88    8b       d8
88b,   ,a8"  88       88  "8a,   ,a8"   88,   "8a,   ,a8"
88`YbbdP"'   88       88   `"YbbdP"'    "Y888  `"YbbdP"'
88                    88
88                    88
                      88
         8b,dPPYba,   88           ,adPPYba,    ,adPPYba,
         88P'   `"8a  88          a8"     "8a  a8"     "8a
         88       88  88          8b       d8  8b       d8
         88       88  88          "8a,   ,a8"  "8a,   ,a8"
	 88       88  88888888888  `"YbbdP"'    `"YbbdP"'
                                    8b,dPPYba,         ,adPPYba,
                                    88P'    "8a       a8"     ""
                                    88       d8       8b
                                    88b,   ,a8"  888  "8a,   ,aa
                                    88`YbbdP"'   888   `"Ybbd8"'
                                    88
                                    88
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
//#include "../globals/utilities.h"
//#include "photonLoop.h"


//== PHOTON LOOP FUNCTION ======================================
void photonLoop(Particle photon[], Planet exo){
//-- ENTRY -----------------------------------------------------
  // Debug printing.
  if (DEBUG){
    printf(ACYAN "Photon Loop Running:\n" ARESET);
  }

  return;  
}
