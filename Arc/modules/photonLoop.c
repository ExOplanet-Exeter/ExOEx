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
double pathLength(Planet*,Particle*);
void checkLife(Planet*,Particle*);
int getLayer(Planet*,double,double,double);
void scatter(Planet*,Particle*);
void isotropic(Particle*);
void move(Planet*,Particle*);

/**/void dev_recordPos(Particle*);


//── FUNCTION IN PROGRESS ─────────────────────────────────────┤
double pathLength(Planet *exo,Particle *photon){
  
  double lambda = -log(arcRand(0.0,1.0)) / exo->kappa[photon->curLayer];
  
  return lambda;
}


//── PHOTON LOOP ──────────────────────────────────────────────┤
void photonLoop(Planet *exo,Particle *photon){

  initialisePhoton(photon);
  stellarEmission(photon);
  mapToPlanetSkin(exo,photon);
  injectPhoton(exo,photon);
  photon->curLayer = getLayer(exo,photon->pos[X],photon->pos[Y],photon->pos[Z]);
  checkLife(exo,photon);
  
  while (photon->life == true){
    scatter(exo,photon);
    move(exo,photon);
    photon->curLayer = getLayer(exo,photon->pos[X],photon->pos[Y],photon->pos[Z]);
    checkLife(exo,photon);
  }
  
  photon->alpha = acos(photon->dirVec[Z]);
    
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

// Calculates the probablity of a photon being absorbed at scatter point.
// Kills the photon if it is absorbed, or if it's left exoplanet.
void checkLife(Planet *exo,Particle *photon){
  
  double A = arcRand(0.0,1.0);  
  if (A > exo->albedo[photon->curLayer]){
    photon->life = false;
  }
  
  double rPhot = sqrt(pow(photon->pos[X],2.0)+pow(photon->pos[Y],2.0)+pow(photon->pos[Z],2.0));
  if (rPhot > 1.0){
    photon->life = false;
  }
  
  return;
}

// Determines the layer that the given (cartesian) coordinates fall within.
int getLayer(Planet *exo,double x,double y,double z){
  
  double rPhot = sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0));
  
  if (rPhot <= exo->radius[0]){
    return 0;
  }
  
  for (int i=0; i<exo->nLayers; i++){
    if ((rPhot > exo->radius[i]) && (rPhot <= exo->radius[i+1])){
      return i;
    }    
  }
  
  // Only other possibility is that photon has left planet.
  return 999;
}

// Determines and calls the correct scattering type function.
void scatter(Planet *exo,Particle* photon){

  int type = exo->scatType[photon->curLayer];
  
  if (type == ISO){
    isotropic(photon);
  }
  else if (type == RAY){
    printErr("RAY type not yet implimented");
  }
  else if (type == MIE){
    printErr("MIE type not yet implimented");
  }
  else {
    printErr("Scatter type unknown");
  }
    
  return;
}

// Creates an isotropic scattering direction.
void isotropic(Particle  *photon){
  
  double phi = arcRand(0.0,2.0*PI);
  double costheta = arcRand(-1.0,1.0);
  double theta = acos(costheta);
  
  photon->dirVec[X] = sin(theta) * cos(phi);
  photon->dirVec[Y] = sin(theta) * sin(phi);
  photon->dirVec[Z] = cos(theta);
  
  double unit = sqrt(pow(photon->dirVec[X],2.0)+pow(photon->dirVec[Y],2.0)+pow(photon->dirVec[Z],2.0));
  if (unit < 0.999999 || unit > 1.000001){
    printErr("Scattering vector is not a unit vector");
    printf("%lf\n",unit);
  }
  
  return;
}

// Moves the photon along the direction vector.
void move(Planet *exo,Particle *photon){
  
  double lambda = pathLength(exo,photon);
  
  for (int i=0; i<3; i++){
    photon->pos[i] += photon->dirVec[i] * lambda;
  }
  
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