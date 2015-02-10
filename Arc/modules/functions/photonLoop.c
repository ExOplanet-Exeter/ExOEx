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
void stellarEmission(Particle*);
void mapToExoSurface(Particle*,Planet*);
void injectPhoton(Particle*,Planet*);
void checkLife(Particle*,Planet*);
double getRho(Particle*);
void isoScatter(Particle*);
void move(Particle*,Planet*);
void getAlpha(Particle*);


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤
double getLambda(Particle *photon,Planet *exo){
	
	return -log(arcRand(0.0,1.0))/exo->lKappa[photon->curLayer];
}


//── PHOTON LOOP ──────────────────────────────────────────────┤
void photonLoop(int i,Particle *photon,Planet *exo){
	
	// Core functions
	initPhoton(photon);
	stellarEmission(photon);
	mapToExoSurface(photon,exo);
	injectPhoton(photon,exo);
	
	while (getRho(photon) <= 1.0 && photon->life == true){
		isoScatter(photon);
		move(photon,exo);
		if (getRho(photon) <= 1.0)
			checkLife(photon,exo);
	}
	
	getAlpha(photon);
	
	return;
}


//── COMPLETED FUNCTIONS ──────────────────────────────────────┤
// Initialises a new photon.
void initPhoton(Particle *photon){
	
	photon->curLayer 	= -1;
	photon->alpha 		= -1.0;
	photon->life		= true;
	
	for(int n=0; n<3; n++){
		photon->pos[n] 		= 0.0;
		photon->dirVec[n]	= 0.0;
	}
		
	return;
}

// Moves photon to a random point on stellar surface.
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

// Moves the photon to the skin of the exoplanet.
// Also changes photons current layer identifier to
// that of the outer most layer.
void mapToExoSurface(Particle *photon,Planet *exo){
	
	double rho = sqrt(pow(photon->pos[X],2.0)+
		pow(photon->pos[Y],2.0));
		
	photon->pos[Z] = sqrt(1.0 - pow(rho,2.0));
	photon->curLayer = exo->nLayers - 1;
	
	return;
}

// Injects the photon in to the exoplanet from skin position.
void injectPhoton(Particle *photon,Planet *exo){
	
	photon->dirVec[Z] = 1.0;
	photon->pos[Z] = photon->pos[Z] - getLambda(photon,exo);
	checkLife(photon,exo);
	
	return;
}

// Determines if the photon was scattered or absorbed after a
// scattering occured. Kills photon if absorbed.
void checkLife(Particle *photon,Planet *exo){
	
	double p = arcRand(0.0,1.0);
	
	if (p > exo->lAlbedo[photon->curLayer])
		photon->life = false;
		
	return;
}

// Calculates the distance of photon from the planets centre.
double getRho(Particle *photon){
	
	double rho;
	
	rho = sqrt(pow(photon->pos[X],2.0)+pow(photon->pos[Y],2.0)+
		pow(photon->pos[Z],2.0));
	
	return rho;
}

// Creates a random direction for scattering.
void isoScatter(Particle *photon){
	
	double theta;
	
	theta = arcRand(0.0, 2.0*PI);
	
	photon->dirVec[X] = 2.0*arcRand(0.0,1.0) -1.0;
	photon->dirVec[Y] = sqrt(1.0 -pow(photon->dirVec[X],2.0)) * 
						cos(theta);
	photon->dirVec[Z] = sqrt(1.0 -pow(photon->dirVec[X],2.0)) *
						sin(theta);
	
	return;
}

// Moves particle distance lambda in direction dirVec.
void move(Particle *photon,Planet *exo){
	
	double lambda = getLambda(photon,exo);
	
	for (int j=0; j<3; j++){
		photon->pos[j] = photon->pos[j] + 
		(photon->dirVec[j]*lambda);
	}
		
	return;
}

// Determines the angle of emission, alpha.
void getAlpha(Particle *photon){
	
	photon->alpha = acos(photon->dirVec[Z]);
	
	return;
}