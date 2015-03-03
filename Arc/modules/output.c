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

      double fittedMax = 0.0;
      for (int i=0; i<179; i++){
            totalData->fittedCurve[i] = totalData->lightcurve[i] / sin((i+0.5)*(PI/180.0));
            if (totalData->fittedCurve[i] > fittedMax){
                  fittedMax = totalData->fittedCurve[i];
            }
      }
      
      // Normalise the fittedCurve.
      for (int i=0; i<180; i++){
            totalData->fittedCurve[i] = totalData->fittedCurve[i]/fittedMax;
            fprintf(file,"%i %lf\n",i,totalData->fittedCurve[i]);
      }
      
      return;
}


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤