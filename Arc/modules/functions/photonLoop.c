/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
  _ __ | |__   ___ | |_ ___  _ __ | |    ___   ___  _ __   ___ 
 | '_ \| '_ \ / _ \| __/ _ \| '_ \| |   / _ \ / _ \| '_ \ / __|
 | |_) | | | | (_) | || (_) | | | | |__| (_) | (_) | |_) | (__ 
 | .__/|_| |_|\___/ \__\___/|_| |_|_____\___/ \___/| .__(_)___|
 |_|                                               |_|
├──────────────────────────────────────────────────────────────┤
	This function is the main particle processing loop of
	ExOEx.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/


//── INCLUDES ─────────────────────────────────────────────────┤
#include "../../globals/headers/global.h"
#include "../../globals/headers/utilities.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
void initPhoton(Particle*);


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤
void stellarEmission(Particle *photon){
	
	double rho = 2.0;
	photon->pos[Z] = STAR_DIST;
	
	while (rho>1.0){
		photon->pos[X] = arcRand(-1.0,1.0);
		photon->pos[Y] = arcRand(-1.0,1.0);
		rho = sqrt(pow(photon->pos[X],2.0)+
			pow(photon->pos[Y],2.0));
	}
	
	return;
}


//── PHOTON LOOP ──────────────────────────────────────────────┤
void photonLoop(Particle *photon,int i){
	
	// Core functions
	initPhoton(photon);
	stellarEmission(photon);
	
	return;
}


//── COMPLETED FUNCTIONS ──────────────────────────────────────┤
void initPhoton(Particle *photon){
	
	photon->curLayer 	= -1;
	photon->alpha 		= -1.0;
	photon->life		= false;
	
	for(int n=0; n<3; n++){
		photon->pos[n] 		= 0.0;
		photon->dirVec[n]	= 0.0;
	}
		
	return;
}