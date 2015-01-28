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


//== OUTPUT FUNCTION ===========================================
void output(Particle photon[], Planet exo, Datasystem data){
    
//-- ENTRY -----------------------------------------------------
  // Debug printing.
  if (DEBUG){
      printf(ACYAN "Output Running:\n" ARESET);
  }

//-- DECLERATIONS ----------------------------------------------
  // Create pointer for output file.
  FILE *output;
  output = fopen("data.dat","w");
  
  if (output == NULL){
    printf(ARED "ERROR! Could not open data.dat!\n" ARESET);
  }

  for (int n=0; n<exo.nPhot; n++){
    fprintf(output,"%lf %lf %lf\n",photon[n].pos[X],
	    photon[n].pos[Y], photon[n].pos[Z]);
  }

  if (DEBUG){
    printf(AGREEN "Output Done.\n" ARESET);
  }    
  return;
}
