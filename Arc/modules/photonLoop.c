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
void   initialisePhoton(Particle*);
void   stellarEmission(Particle*);
void   mapToPlanetSurface(Particle*,Planet*);
void   injectPhoton(Particle*,Planet*);
double getRho(Particle*);
void   scatter(Particle*,Planet*);
void   isotropic(Particle*);
void   move(Particle*,Planet*);
void   absorbeChance(Particle*,Planet*);
void   getAlpha(Particle*);
/**/ void devTesting(Particle*);


//── PHOTON LOOP ──────────────────────────────────────────────┤
void photonLoop(Planet *exo,Particle *photon){

  initialisePhoton(photon);
  stellarEmission(photon);
  mapToPlanetSurface(photon,exo);
  
  injectPhoton(photon,exo);
  
  while (getRho(photon) <= 1.0 && photon->life == true){
    if (exo->scatType[photon->curLayer] == ISO){
      scatter(photon,exo);
      move(photon,exo);
      if (getRho(photon) <= 1.0){
        absorbeChance(photon,exo);
      }
    }
    
  }
  
  getAlpha(photon);
  
  devTesting(photon);

	return;
}


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤
double getLambda(Particle *photon,Planet *exo){
  
  double lambda = -log(arcRand(0.0,1.0))/exo->kappa[photon->curLayer];
  
  return lambda;
}


//─── COMPLETED FUNCTIONS ─────────────────────────────────────┤
// This function is used for developer testing only. Do not 
// leave enabled. Should only be run with a single thread.
/**/ void devTesting(Particle *photon){
  
  FILE *file;
  
  file = fopen("../../Output/position.dat","a");
  
  if (file == NULL)
    printErr("Somethign /has/ gone wrong");
  
  fprintf(file,"%lf %lf %lf\n",photon->pos[X],photon->pos[Y],photon->pos[Z]);
  
  fclose(file);
  
  return;  
}

// Initialises a new photon.
void initialisePhoton(Particle *photon){
  
  photon->curLayer    = -1;
  photon->alpha       = -1.0;
  photon->life        = true;
  photon->wavelength  = 0.0;
  
  for (int i=0; i<3; i++){
    photon->pos[i]    = 0.0;
    photon->dirVec[i] = 0.0;
  }
  
  return;
}

// Moves the new photon to a random point at the stellar surface.
void stellarEmission(Particle *photon){
  // rho must be initialised to > 1.0.
  double rho = 2.0;
  
  photon->pos[Z] = STAR_DIST;
  
  while (rho > 1.0){
    photon->pos[X] = arcRand(-1.0,1.0);
    photon->pos[Y] = arcRand(-1.0,1.0);
    
    rho = sqrt(pow(photon->pos[X],2.0)+pow(photon->pos[Y],2.0));
  }
  
  return;
}

// Maps the photons from the point of emission to the
// exoplanets surface.
void mapToPlanetSurface(Particle *photon,Planet *exo){
  
  double rho;
  rho = sqrt(pow(photon->pos[X],2.0)+pow(photon->pos[Y],2.0));
  
  photon->pos[Z] = sqrt(1.0 - pow(rho,2.0));
  
  photon->curLayer = exo->nLayers - 1;
  
  return;
}

// Injects the photon into the exoplanet from its skin position.
void injectPhoton(Particle *photon,Planet *exo){
  
  photon->dirVec[X] = 0.0;
  photon->dirVec[Y] = 0.0;
  photon->dirVec[Z] = 1.0;
  
  photon->pos[Z] = photon->pos[Z] - getLambda(photon,exo);
  
  absorbeChance(photon,exo);
  
  return;
}

// Calculates the distance of a particle from the centre of the planet.
double getRho(Particle *photon){
  
  double rho, sum = 0.0;
  
  for (int i=0; i<3; i++){
    sum += pow(photon->pos[i],2.0);
  }
  
  rho = sqrt(sum);
  
  return rho;
}

// Creates an new appropriate dirVec.
void scatter(Particle *photon,Planet *exo){
  
  int type = exo->scatType[photon->curLayer];
  
  if (type == ISO){
    isotropic(photon);
  }
  
  else if (type == RAY){
    printf("RAY scatter.\n");
  }
  
  else if (type == MIE){
    printf("MIE scatter.\n");
  }
  
  else {
    printErr("Unknown scatter type!");
  }
  
  return;
}

// Performs an isotropic scattering.
void isotropic(Particle *photon){
  
  double theta;
  
  theta = arcRand(0.0,2.0*PI);
  
  photon->dirVec[X] = 2.0*arcRand(0.0,1.0) - 1.0;
  photon->dirVec[Y] = sqrt(1.0 - pow(photon->dirVec[X],2.0)) * cos(theta);
  photon->dirVec[Z] = sqrt(1.0 - pow(photon->dirVec[X],2.0)) * sin(theta);
  
  return;
}

// Move the photon a length along its dirVec.
void move(Particle *photon,Planet *exo){
  
  double lambda = getLambda(photon,exo);
  
  for (int i=0; i<3; i++){
    photon->pos[i] += photon->dirVec[i] * lambda;
  }
  
  return;
}

// Determines, from the layer albedo, if a photon has been absorbed.
void absorbeChance(Particle *photon,Planet *exo){
  
  double x = arcRand(0.0,1.0);
  
  if ( x > exo->albedo[photon->curLayer])
    photon->life = false;
  
  return;
}

// Determines the value of alpha, the angle, relative to the angle of entry,
// that the photon leaves the exoplanet.
void getAlpha(Particle *photon){
  
  photon->alpha = acos(photon->dirVec[Z]);
  
  return;
}