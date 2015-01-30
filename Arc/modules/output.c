/*==============================================================
----------------------------------------------------------------
                            ,d
                            88
 ,adPPYba,   88       88  MM88MMM  8b,dPPYba,   88       88
a8"     "8a  88       88    88     88P'    "8a  88       88
8b       d8  88       88    88     88       d8  88       88
"8a,   ,a8"  "8a,   ,a88    88,    88b,   ,a8"  "8a,   ,a88
 `"YbbdP"'    `"YbbdP'Y8    "Y888  88`YbbdP"'    `"YbbdP'Y8
                                   88     ,d
                                   88     8*
                                        MM88MMM        ,adPPYba,
                                          88          a8"     ""
                                          88          8b
                                          88,    888  "8a,   ,aa
                                          "Y888  888   `"Ybbd8"'
----------------------------------------------------------------
    The output function takes data created by the photonLoop
    function in the form of an array of photons, and outputs
selected parts of the data into .dat files and graphical plots.
----------------------------------------------------------------
==============================================================*/


//== INCLUDES ==================================================
//-- SYSTEM HEADERS --------------------------------------------
// Allows use of math functions such as sine/cosine etc.

//-- LOCAL HEADERS ---------------------------------------------
#include "../globals/global.h"
#include "headers/output.h"
#include <math.h>


//== OUTPUT FUNCTION ===========================================
void output(Particle photon[], Planet exo, Datasystem data){
    
//-- ENTRY -----------------------------------------------------
  // Debug printing.
  if (DEBUG){
      printf(ACYAN "Output Running:\n" ARESET);
  }

//-- DECLERATIONS ----------------------------------------------
  int totalDead = 0.0, angle;
  double percentDead, lightcurveBin[180] = {0.0};

  // Create pointer for output file.
  FILE *position, *lightcurve, *deadPos;
  position   = fopen("data/position.dat","w");
  lightcurve = fopen("data/lightcurve.dat","w");
  deadPos    = fopen("data/deadPosition.dat","w");
  
  if (position == NULL){
    printf(ARED "ERROR! Could not open position.dat!\n" ARESET);
  }
  if (lightcurve == NULL){
    printf(ARED "ERROR! Could not open lightcurve.dat!\n" ARESET);
  }
  if (deadPos == NULL){
    printf(ARED "ERROR! Could not open deadPosition.dat!\n" ARESET);
  }

  for (int n=0; n<exo.nPhot; n++){
    angle = photon[n].alpha*(180.0/PI) /1;
    lightcurveBin[angle]++;
    if (photon[n].life != 0){
      totalDead++;
      fprintf(deadPos,"%lf %lf %lf\n",photon[n].pos[X],
	      photon[n].pos[Y], photon[n].pos[Z]);
    }
    if (photon[n].life == 0){
      fprintf(position,"%lf %lf %lf\n",photon[n].pos[X],
              photon[n].pos[Y], photon[n].pos[Z]);
    }
  }

  for (int i=0; i<180; i++){
    lightcurveBin[i] = lightcurveBin[i] / sin(((i+0.5)*(PI/180.0)));
    fprintf(lightcurve,"%i %lf\n",i,lightcurveBin[i]);
  }

  percentDead = (totalDead*100.0)/exo.nPhot;
  printf("%i/%i photons dead. (%lf%%)\n",
	 totalDead,exo.nPhot,percentDead);

  if (DEBUG){
    printf(AGREEN "Output Done.\n" ARESET);
  }    
  return;
}
