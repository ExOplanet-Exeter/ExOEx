/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
             ___  _   _| |_ _ __  _   _| |_   ___ 
            / _ \| | | | __| '_ \| | | | __| / __|
           | (_) | |_| | |_| |_) | |_| | |_ | (__ 
            \___/ \__,_|\__| .__/ \__,_|\__(_)___|
                           |_|             
├──────────────────────────────────────────────────────────────┤
	Outputs the contents of the totalData structure into files.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "../globals/global.h"
#include "../globals/utilities.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤


//── OUTPUT ───────────────────────────────────────────────────┤
void output(Datasystem *totalData){

      FILE* file;
      
      if (globalRunningMode == NORMAL){
            file = fopen(outputPath "lightcurve.dat","w");
      }
      else if (globalRunningMode == LAMBERT){
            file = fopen(outputPath "lambertian.dat","w");
      }
      
      if (file == NULL){
            printErr("Could not open lightcurve.dat");
      }
      
      printf("nDead = %i\n",totalData->nDead);

      double fittedMax = 0.0, iMax = 0.0, qMax = 0.0, uMax = 0.0, vMax = 0.0;
      for (int i=0; i<179; i++){
            totalData->fittedCurve[i] = totalData->lightcurve[i] / sin((i+0.5)*(PI/180.0));
            totalData->IPol[i] = totalData->IPol[i] / sin((i+0.5)*(PI/180.0));
            totalData->QPol[i] = totalData->QPol[i] / sin((i+0.5)*(PI/180.0));
            totalData->UPol[i] = totalData->UPol[i] / sin((i+0.5)*(PI/180.0));
            totalData->VPol[i] = totalData->VPol[i] / sin((i+0.5)*(PI/180.0));
            if (totalData->fittedCurve[i] > fittedMax){
                  fittedMax = totalData->fittedCurve[i];
            }
            if (totalData->IPol[i] > iMax){
                  iMax = totalData->IPol[i];
            }
            if (totalData->QPol[i] > qMax){
                  qMax = totalData->QPol[i];
            }
            if (totalData->UPol[i] > uMax){
                  uMax = totalData->UPol[i];
            }
            if (totalData->VPol[i] > vMax){
                  vMax = totalData->VPol[i];
            }
      }
      
      // Normalise the fittedCurve.
      for (int i=0; i<180; i++){
            totalData->fittedCurve[i] = totalData->fittedCurve[i]/fittedMax;
            totalData->IPol[i] = totalData->IPol[i]/iMax;
            totalData->QPol[i] = totalData->QPol[i]/qMax;
            totalData->UPol[i] = totalData->UPol[i]/uMax;
            totalData->VPol[i] = totalData->VPol[i]/vMax;
            fprintf(file,"%i %lf %lf %lf %lf %lf\n",i,totalData->fittedCurve[i],totalData->IPol[i],totalData->QPol[i],totalData->UPol[i],totalData->VPol[i]);
            printf("%i %lf %lf %lf %lf %lf\n",i,totalData->fittedCurve[i],totalData->IPol[i],totalData->QPol[i],totalData->UPol[i],totalData->VPol[i]);
      }
      
      return;
}


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤