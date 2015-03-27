/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
       _ __ ___  __| |_   _  ___| |_(_) ___  _ __    ___ 
      | '__/ _ \/ _` | | | |/ __| __| |/ _ \| '_ \  / __|
      | | |  __/ (_| | |_| | (__| |_| | (_) | | | || (__ 
      |_|  \___|\__,_|\__,_|\___|\__|_|\___/|_| |_(_)___|        
├──────────────────────────────────────────────────────────────┤
	This part of the program revolves around reducing the data
	from the indervidual threads into a single strucuture.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "../globals/global.h"
#include "../globals/utilities.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤


//── REDUCTION ────────────────────────────────────────────────┤
void reduction(ThreadInfo *thread,Datasystem *totalData){

      totalData->nDead += thread->data.nDead;
      
      for (int i=0; i<180; i++){
            totalData->lightcurve[i] += thread->data.lightcurve[i];
            totalData->IPol[i] += thread->data.IPol[i];
            totalData->QPol[i] += thread->data.QPol[i];
            totalData->UPol[i] += thread->data.UPol[i];
            totalData->VPol[i] += thread->data.VPol[i];
      }
      
	return;
}


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤