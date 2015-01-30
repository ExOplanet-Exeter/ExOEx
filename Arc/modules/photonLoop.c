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
#include "../globals/utilities.h"
#include "headers/photonLoop.h"


//== FUNCTIONS IN PROGRESS =====================================
// Calculates the emission angle (alpha) of a photon.
double getAlpha(Particle photon){
  double alpha;
  alpha = acos(arcDot(photon.dirVec[X],photon.dirVec[Y],
		      photon.dirVec[Z],0.0,0.0,1.0));
  return alpha;
}


// Moves the photon to a new position along the direction vector
// with a total displacement lambda.
Particle move(Particle photon, Planet exo){
  double lambda;
  lambda = getLambda(photon, exo);
  for (int i=0; i<3; i++){
    photon.pos[i] = photon.pos[i] + (photon.dirVec[i] * lambda);
  }
  return photon;
}


// Create a direction vector for an isotropic scattering.
Particle isoScatter(Particle photon){
  double theta;
  theta            = arcRand(0.0,2.0*PI);
  photon.dirVec[X] = 2.0 * arcRand(0.0,1.0) - 1.0;
  photon.dirVec[Y] = sqrt(1.0 - pow(photon.dirVec[X],2.0)) * 
    cos(theta);
  photon.dirVec[Z] = sqrt(1.0 - pow(photon.dirVec[X],2.0)) * 
    sin(theta);
  return photon;
}

// Gives the photon a chance to be absorbed and thus removed
// from photon loop.
int absorbeChance(Particle photon, Planet exo){
  double a;
  a = arcRand(0.0,1.0);
  if (a < exo.layerAlbedo[photon.curLayer]){
    return 0;
  }
  else{
    return 1;
  }
}


// 'Inject' the photon in along direction vector connecting star
// and exoplanet, as photons are emitted normal to stellar 
// surface.
Particle injectPhoton(Particle photon, Planet exo){
  photon.pos[Z] = photon.pos[Z] - getLambda(photon,exo);
  photon = getLayer(photon, exo);
  if(getRho(photon) <= 1.0){
    photon.life = absorbeChance(photon,exo);
  }
  return photon;
}


//== PHOTON LOOP FUNCTION ======================================
void photonLoop(Particle photon[], Planet exo){
//-- ENTRY -----------------------------------------------------
  // Debug printing.
  if (DEBUG){
    printf(ACYAN "Photon Loop Running:\n" ARESET);
  }

//-- DECLERATIONS ----------------------------------------------
  
//-- PHOTON LOOP -----------------------------------------------
  for (int n=0; n<exo.nPhot; n++){
    photon[n] = initPhoton(photon[n], n);
    photon[n] = stellarEmission(photon[n]);
    photon[n] = mapToExoSurface(photon[n], exo);
    photon[n] = injectPhoton(photon[n], exo);
    while (getRho(photon[n]) <= 1.0 && photon[n].life == 0){
      photon[n] = isoScatter(photon[n]);
      photon[n] = move(photon[n], exo);
      if(getRho(photon[n]) <= 1.0){
	photon[n].life = absorbeChance(photon[n],exo);
      }
    }
    photon[n].alpha = getAlpha(photon[n]);
  }

  if (DEBUG){
    printf(AGREEN "Photon Loop Done.\n" ARESET);
  }
  return;  
}
