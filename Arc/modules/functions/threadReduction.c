/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
	  _____  _| |_ _ __ __ _  ___| |_(_) ___  _ __    ___ 
	 / _ \ \/ / __| '__/ _` |/ __| __| |/ _ \| '_ \  / __|
	|  __/>  <| |_| | | (_| | (__| |_| | (_) | | | || (__ 
	 \___/_/\_\\__|_|  \__,_|\___|\__|_|\___/|_| |_(_)___|
├──────────────────────────────────────────────────────────────┤
	This function extracts meaningful data from the particle
	structure and stores it into a Datasystem structure.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "../../globals/headers/global.h"
#include "../../globals/headers/utilities.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤


//── PHOTON LOOP ──────────────────────────────────────────────┤
void threadReduction(Datasystem *threadData,Datasystem *globalData){

	for (int i=0; i<180; i++){
		globalData->lightCurve[i] += threadData->lightCurve[i];
	}
	
	return;
}


//── COMPLETED FUNCTIONS ──────────────────────────────────────┤