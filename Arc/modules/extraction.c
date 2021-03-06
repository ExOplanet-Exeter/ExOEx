/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
      _____  _| |_ _ __ __ _  ___| |_(_) ___  _ __    ___ 
     / _ \ \/ / __| '__/ _` |/ __| __| |/ _ \| '_ \  / __|
    |  __/>  <| |_| | | (_| | (__| |_| | (_) | | | || (__ 
     \___/_/\_\\__|_|  \__,_|\___|\__|_|\___/|_| |_(_)___|           
├──────────────────────────────────────────────────────────────┤
	Extracts data from a particle type and stores it in the
	threadInfo type.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "../globals/global.h"
#include "../globals/utilities.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤


//── EXTRACTION ───────────────────────────────────────────────┤
void extraction(Particle *photon,ThreadInfo *thread){

      int theta = photon->alpha * (180.0/PI);

      if (photon->life == false){
            thread->data.nDead++;
      }
      else {
            thread->data.lightcurve[theta]++;
            thread->data.IPol[theta] += photon->pol[I];
            thread->data.QPol[theta] += photon->pol[Q];
            thread->data.UPol[theta] += photon->pol[U];
            thread->data.VPol[theta] += photon->pol[V];
      }

	return;
}

//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤