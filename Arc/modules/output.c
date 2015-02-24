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
	
	if (DEBUG)
		printStart("Output");
		
				
	FILE *file;
	file = fopen(outputPath "lightcurve.dat","w");
	
	if (file == NULL)
		printErr("Could not open lightcurve.dat");
		
		
	printf("Number of dead photons: %i.\n",totalData->nDead);
		
	for (int i=0; i<180; i++){
		totalData->fittedCurve[i] = totalData->lightcurve[i] / sin((i+0.5)*(PI/180.0));
		//printf("%i %i %lf\n",i,totalData->lightcurve[i],totalData->fittedCurve[i]);
	}
	totalData->fittedCurve[0] = totalData->fittedCurve[1];
	
	
	for (int i=0; i<180; i++){
		fprintf(file,"%i %lf\n",i,totalData->fittedCurve[i]);
	}
	
		
	if (DEBUG)
		printEnd("Output");
	
	return;
}


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤