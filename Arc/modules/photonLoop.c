/*═════════════════════════════════════════════════════════════╗
├──────────────────────────────────────────────────────────────┤
  _ __ | |__   ___ | |_ ___  _ __ | |    ___   ___  _ __   ___ 
 | '_ \| '_ \ / _ \| __/ _ \| '_ \| |   / _ \ / _ \| '_ \ / __|
 | |_) | | | | (_) | || (_) | | | | |__| (_) | (_) | |_) | (__ 
 | .__/|_| |_|\___/ \__\___/|_| |_|_____\___/ \___/| .__(_)___|
 |_|                                               |_|          
├──────────────────────────────────────────────────────────────┤
	This is the main computation core of ./arc.
├──────────────────────────────────────────────────────────────┤
╚═════════════════════════════════════════════════════════════*/

//── INCLUDES ─────────────────────────────────────────────────┤
#include "../globals/global.h"
#include "../globals/utilities.h"


//── FUNCTION PROTOTYPES ──────────────────────────────────────┤
void initialisePhoton(Particle*);
void stellarEmission(Particle* photon);
void mapToPlanetSkin(Planet*,Particle*);
void injectPhoton(Planet*,Particle*);
/**/void dev_recordPos(Particle*);


//── FUNCTION IN PROGRESS ─────────────────────────────────────┤
double pathLength(Planet* exo,Particle* photon){
  
  double tau = -log(arcRand(0.0,1.0));
  
  int impactLayer = layerToHit(exo,photon);
  
  // Get distance to layer
  // Times that by kappa for tau'
  // Add tau' to totalTau
  // Is totalTau > tau?
  //  yes -> do more calc
  //  no -> find fraction it falls short
    
  return arcRand(0.0,1.0);
}

int layerToHit(Planet *exo,Particle *photon){
  
  // Photon will always exit inner most layer.
  if (photon->curLayer == 0){
    return 0;
  }
  
  double rPhot, rInner, rCrit;
  rPhot = sqrt(pow(photon->pos[X],2.0)+pow(photon->pos[Y],2.0)+pow(photon->pos[Z],2.0));
  rInner= exo->radius[photon->curLayer];
  rCrit = sqrt(pow(rPhot,2.0)+pow(rInner,2.0));
  
  double ghostPos[3];
  for (int i=0; i<3; i++){
    ghostPos[i] = photon->pos[i] + (photon->dirVec[i]*rCrit);
  }
  
  if (getLayer(exo,ghostPos[X],ghostPos[Y],ghostPos[Z]) < photon->curLayer){
    // Then photon is hitting inner layer;
    return photon->curLayer - 1;
  }
  else {
    // Then photon is hitting outer boundary of current layer.
    return photon->curLayer;
  }
}

int getLayer(Planet *exo,double x,double y,double z){

  double rho = sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0));
  if (rho > 1.0){
    return 999;
  }
  
  for(int i=0; i<exo->nLayers; i++){
    if ((rho > exo->radius[i]) && (rho <= exo->radius[i+1])){
      return i+1;
    }
  }

  // If not already returned it must be in core layer (0);
  return 0; 
}


//── PHOTON LOOP ──────────────────────────────────────────────┤
void photonLoop(Planet *exo,Particle *photon){

  initialisePhoton(photon);
  stellarEmission(photon);
  mapToPlanetSkin(exo,photon);
  injectPhoton(exo,photon);
  
  dev_recordPos(photon);

  return;
}


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤
// Initialises the properties of a new particle.
void initialisePhoton(Particle *photon){
  
  photon->life     = true;
  photon->curLayer = -1; 
  //photon->wavelength...
  photon->alpha    = 0.0; 
  
  for (int i=0; i<3; i++){
    photon->pos[i] = 0.0;
    photon->dirVec[i] = 0.0;
  }
  
  return;
}

// Moves photon to random point on stellar surface.
void stellarEmission(Particle* photon){
  
  photon->pos[X] = arcRand(-1.0,1.0);
  photon->pos[Y] = arcRand(-1.0,1.0);
  photon->pos[Z] = STAR_DIST;
  
  double rho = sqrt(pow(photon->pos[X],2.0) + pow(photon->pos[Y],2.0));
  
  while (rho > 1.0){
    photon->pos[X] = arcRand(-1.0,1.0);
    photon->pos[Y] = arcRand(-1.0,1.0);
    rho = sqrt(pow(photon->pos[X],2.0) + pow(photon->pos[Y],2.0));
  }
  
  return;
}

// Moves the photons from the stellar surface to the planets outermost surface.
void mapToPlanetSkin(Planet *exo,Particle *photon){

  photon->curLayer  = exo->nLayers - 1;
  photon->dirVec[Z] = -1.0;

  double rho = sqrt(pow(photon->pos[X],2.0) + pow(photon->pos[Y],2.0));
  photon->pos[Z] = sqrt(1.0 - pow(rho,2.0));  
  
  return;
}

// Provides the initial injection of photons into the
// planet along the Z-axis.
void injectPhoton(Planet *exo,Particle *photon){
  
  double lambda = pathLength(exo,photon);
  
  photon->pos[Z] -= lambda;
  
  return;
}



// Developer function: Record the position of photon to a file.
/**/void dev_recordPos(Particle* photon){
  
  FILE* file;
  file = fopen(outputPath "position.dat","a");
  
  fprintf(file, "%lf %lf %lf\n",photon->pos[X],photon->pos[Y],photon->pos[Z]);
  
  fclose(file);
  
  return;
}