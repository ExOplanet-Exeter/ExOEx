/*
  This function allows data being printed to a file and also
  allows the data to be graphically plotted via a gnuPlot
  pipeline
*/

//================================================== INCLUDES ==
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "global.h"
#include "gnuplot_i.h"                                          // Used for graphical output

#define PI 3.14159265359


//======================================= FUNCTION PROTOTYPES ==
int degConvert(double);                                         // Simply converts from radians to degrees


//============================================= MAIN FUNCTION ==
void output(Particle photon[], Planet exo) {
  if (DEBUG)
    printf(ACYAN "\nStage: Output\n" ARESET);

  // Declerations
  gnuplot_ctrl *gnup;                                           // Create pointer for gnuPlot
  gnup = gnuplot_init();                                        // Create handle for gnuPlot
  int lightcurve[180] = {0};                                    // Data storage for emission angle

  // Setting up GNU plot window
  gnuplot_setstyle(gnup, "impulses");                           // Style
  gnuplot_set_xlabel(gnup, "Emission angle");                   // X-axis label
  gnuplot_set_ylabel(gnup, "Frequency");                        // Y-axis label

  // Write to file
  FILE *output;                                                 // Create pointer for output folder
  output = fopen("lightcurve.dat","w");                         // Output file handle
  if (output == NULL)
    printf(ARED "ERROR: Could not open lightcurve.dat\n" ARESET);

  for (int n=0; n<exo.nPhot; n++) {
    //fprintf(output, "%lf %lf %lf\n",photon[n].pos[X],photon[n].pos[Y],photon[n].pos[Z]);
    //printf("%i %lf\n",photon[n].identity,photon[n].alpha);
    lightcurve[degConvert(photon[n].alpha)] = lightcurve[degConvert(photon[n].alpha)] + 1;
  }

  for (int i=0; i<180; i++) {
    fprintf(output,"%i %lf\n",i,(lightcurve[i]/sin(PI/(i+0.5))));
    //printf("%i %lf\n",i,(lightcurve[i]/sin(3.142/(i+0.5))));
  }

  // Clean up
  fclose(output);

  // GNU plotting
  FILE *dataRead;                                               // Pointer for reading file
  dataRead = fopen("lightcurve.dat","r");                       // Handle for reading file
  if (output == NULL)
    printf(ARED "ERROR: Could not open lightcurve.dat\n" ARESET);

  //gnuplot_cmd(gnup,"set size ratio -1");
  gnuplot_cmd(gnup,"plot [0:180] [0:25000] 'lightcurve.dat'");   // Issues a commange to gunPlot
  printf("Data is saved in lightcurve.txt\n");

  // Clean up
  gnuplot_close(gnup);
  fclose(output);

  return;
}


//====================================== ADDITIONAL FUNCTIONS ==
// Converts from doulbe radian to integer degree
int degConvert(double rad) {
  int deg;
  deg = (rad/PI)*180;
  return deg;
}
