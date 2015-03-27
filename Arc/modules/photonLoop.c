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
void stellarEmission(Particle*);
void mapToPlanetSkin(Planet*,Particle*);
double getRho(Particle*);
int layerToHit(Planet*,Particle*);
double distToLayer(Planet*,Particle*,int);
void injectPhoton(Planet*,Particle*);
double pathLength(Planet*,Particle*);
int getLayer(Planet*,double,double,double);
void absorbe(Planet*,Particle*);
void scatter(Planet*,Particle*);
void randomDirection(Particle*);
void isotropic(Particle*);
void rayleigh(Particle*);
void move(Planet*,Particle*);
void moveBack(Particle*);
void moveBack(Particle*);
void observerPol(Particle*);
/**/ void dev_recordPos(Particle*);
/**/ void dev_observe(Particle*);
/**/ void dev_look(Particle*);
/**/ void dev_recordPol(Particle*);


//── FUNCTIONS IN PROGRESS ────────────────────────────────────┤


//── PHOTON LOOP ──────────────────────────────────────────────┤
void photonLoop(Planet *exo,Particle *photon){
  
  initialisePhoton(photon);
  stellarEmission(photon);
  mapToPlanetSkin(exo,photon);
  
  
  if (globalRunningMode == NORMAL){
    injectPhoton(exo,photon);
    if (getRho(photon) <= 1.0){
      photon->curLayer = getLayer(exo,photon->pos[X],photon->pos[Y],photon->pos[Z]);
      absorbe(exo,photon);
    }
    while ((photon->life == true) && (getRho(photon) <= 1.0)){
      
      scatter(exo,photon);
      move(exo,photon);
      if (getRho(photon) <= 1.0){
        photon->curLayer = getLayer(exo,photon->pos[X],photon->pos[Y],photon->pos[Z]);
        absorbe(exo,photon);
      }
    }
  }
  
  if (photon->life == true){
    moveBack(photon);
    photon->alpha = acos(photon->dirVec[Z]);
  }
  else {
    photon->alpha = -1.0;  
  }
  
  observerPol(photon);
  
  //printf("%lf %lf %lf %lf\n",photon->pol[I],photon->pol[Q],photon->pol[U],photon->pol[V]);
  
  //dev_recordPos(photon);
  //dev_observe(photon);
  //dev_look(photon);
  //dev_recordPol(photon);
  
  return;
}


//── COMPLETED FUNCTIONS ──────────────────────────────────────┤
// Initialises all of the Particle structure's variables.
void initialisePhoton(Particle *photon){
  
  photon->life    = true;
  photon->curLayer= -1;
  photon->alpha   = -1.0;
  
  photon->pol[I] = 1.0;
  photon->pol[Q] = arcRand(-1.0,1.0);
  photon->pol[U] = arcRand(-1.0,1.0);
  photon->pol[V] = arcRand(-1.0,1.0);
  
  photon->norm[X] = arcRand(-1.0,1.0);
  photon->norm[Y] = sqrt(1.0 - pow(photon->norm[X],2.0));
  photon->norm[Z] = 0.0;
  
  photon->lambda = 0.0;
  
  for (int i=0; i<3; i++){
    photon->pos[i]    = 0.0;
    photon->dirVec[i] = 0.0;
  }
  
  return;
}

// Moves the photon to a random location on the stellar surface.
void stellarEmission(Particle *photon){
  
  double rho = 2.0;
  
  while (rho > 1.0){
    photon->pos[X] = arcRand(-1.0,1.0);
    photon->pos[Y] = arcRand(-1.0,1.0);
    rho = sqrt(pow(photon->pos[X],2.0)+pow(photon->pos[Y],2.0));
  }
  
  photon->pos[Z] = STAR_DIST;
  
  return;
}

// Maps the Particles to the skin of the Planet.
void mapToPlanetSkin(Planet *exo,Particle *photon){
  
  photon->curLayer = exo->nLayers - 1;
  photon->dirVec[Z] = -1.0;
  
  double rho = sqrt(pow(photon->pos[X],2.0)+pow(photon->pos[Y],2.0));
  
  photon->pos[Z] = sqrt(1.0 - pow(rho,2.0));
  
  return;
}

// 'Injects' the particles once into the planet.
void injectPhoton(Planet* exo,Particle *photon){
  
  double lambda = pathLength(exo,photon);
  
  photon->pos[Z] -= lambda;
  
  return;
}

// Calculates the distance of a photon from the core of the 
// planet (rho).
double getRho(Particle *photon){
  
  return sqrt(pow(photon->pos[X],2.0)+pow(photon->pos[Y],2.0)+pow(photon->pos[Z],2.0));
}

// Determines what layer the particle will hit if it travels
// along its current dirVec.
int layerToHit(Planet *exo,Particle *photon){
  
  if (photon->curLayer == 0){
    return 0;
  }
  
  double innerRadius = exo->radius[photon->curLayer - 1];
  double photRadius = getRho(photon);
  
  double theta = asin(innerRadius/photRadius);
  double phi = acos((photon->dirVec[X]*-photon->pos[X])+(photon->dirVec[Y]*-photon->pos[Y])+(photon->dirVec[Z]*-photon->pos[Z]));
  
  if (phi <= theta){
    return photon->curLayer - 1;
  }
  else {
    return photon->curLayer;
  }
}

// Calculates the distance a photon will travel before a
// scattering event will occure.
double pathLength(Planet *exo,Particle *photon){
  
  double pos[3] = {0.0};
  int curLayer = -1;
  
  for (int i=0; i<3; i++){
    pos[i] = photon->pos[i];
  }
  curLayer = photon->curLayer;
  
  double tau = -log(arcRand(0.0,1.0));
  double lambda = 0.0;
  
  
  while(tau > 0.0){
    
    if (sqrt(pow(pos[X],2.0)+pow(pos[Y],2.0)+pow(pos[Z],2.0)) > 1.0){
      //return distToLayer(exo,photon,exo->nLayers-1)+1.0;
      return -log(arcRand(0.0,1.0))/exo->kappa[photon->curLayer];      // WARNING! WORDINGHAM FUDGE!
    }
    
    int impactLayer = layerToHit(exo,photon);
    double lambdaPrime = distToLayer(exo,photon,impactLayer);
    double tauPrime = lambdaPrime * exo->kappa[curLayer];
    
    if ((tau - tauPrime) > 0.0){
      tau -= tauPrime;
      lambda += lambdaPrime;
      for (int i=0; i<3; i++){
        pos[i] += lambdaPrime * photon->dirVec[i];
      }
      curLayer = impactLayer;
    }
    else {
      double frac = tau/tauPrime;
      for (int i=0; i<3; i++){
        pos[i] += frac * lambdaPrime * photon->dirVec[i];
      }
      lambda += lambdaPrime * frac;
      tau = -1.0;
    }
  }
  
  return lambda;
}

// Calculates the distance a particle may travel in dirVec
// before impacting a layer.
double distToLayer(Planet *exo,Particle *photon,int impactLayer){
 
  double alpha = acos((photon->dirVec[X]*-photon->pos[X])+(photon->dirVec[Y]*-photon->pos[Y])+(photon->dirVec[Z]*-photon->pos[Z]));
  double A = exo->radius[impactLayer];
  double C = getRho(photon);
  
  double lambdaA = (C*cos(alpha)) + sqrt(pow(A,2.0)+(pow(C,2.0)*pow(cos(alpha),2.0))-pow(C,2.0));
  double lambdaB = (C*cos(alpha)) - sqrt(pow(A,2.0)+(pow(C,2.0)*pow(cos(alpha),2.0))-pow(C,2.0));

  if (fabs(lambdaB)>0.00001){
    return lambdaB;
  }
  else {
    return lambdaA;
  }
}

// Determines the layer that a photon currently is located in
// from 3 cartesian position coordinates.
int getLayer(Planet *exo,double x, double y, double z){
  
  int layer;
  double rPhot = sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0));
  
  if (rPhot > 1.0){
    printf("Asking for layer when it's already gone!\n");
  }
  
  if (rPhot <= exo->radius[0]){
    return 0;
  }
  else {
    for (int i=1; i<exo->nLayers; i++){
      if ((rPhot > exo->radius[i-1]) && (rPhot <= exo->radius[i])){
        return i;
      }
    }
  }
}

// Kills the photon if it's absorbed or has left the exoplanet.
void absorbe(Planet *exo,Particle *photon){
  
  if ((photon->curLayer >= 0) && (photon->curLayer < exo->nLayers)){
    
    double A = arcRand(0.0,1.0);
    
    if (A > exo->albedo[photon->curLayer]){
      photon->life = false;
    }
  }
  
  return;
}

void scatter(Planet *exo,Particle *photon){
  
  if (exo->scatType[photon->curLayer] == ISO){
    isotropic(photon);
  }
  if (exo->scatType[photon->curLayer] == RAY){
    rayleigh(photon);
  }
  if (exo->scatType[photon->curLayer] == MIE){
  }
  
  return;
}

void randomDirection(Particle *photon){
  
  double w, u, v, theta;
  
  w = arcRand(0.0,2.0) - 1.0;
  theta = arcRand(0.0,2.0*PI);
  u = sqrt(1.0 - pow(w,2.0)) * cos(theta);
  v = sqrt(1.0 - pow(w,2.0)) * sin(theta);
  
  photon->dirVec[X] = w;
  photon->dirVec[Y] = u;
  photon->dirVec[Z] = v;
  
  return;
}

void isotropic(Particle *photon){
  
  randomDirection(photon);
  
  return;
}

void rayleigh(Particle *photon){
  
  double A, B, dotProd;
  double u[3] = {0.0};
  
  for (int i=0; i<3; i++){
    u[i] = photon->dirVec[i];
  }
  
  bool done = false;
  
  while (done == false){
    A = arcRand(0.0,2.0);
    randomDirection(photon);
    dotProd = acos((photon->dirVec[X]*u[X])+(photon->dirVec[Y]*u[Y])+(photon->dirVec[Z]*u[Z]));
    B = 1.0 + pow(cos(dotProd),2.0);
    if (B >= A){
      done = true;
    }
  }
  
  // This is where polarisation happens
  // u[] is incoming, v[] is outgoing, n[] is normal.
  
  double v[3]={0.0}, o[3]={0.0}, n[3]={0.0};
  
  for (int i=0; i<3; i++){
    v[i] = photon->dirVec[i];
    o[i] = photon->norm[i];
  }
  
  n[X] = (u[Y]*v[Z]) - (u[Z]*v[Y]);
  n[Y] = - ((u[X]*v[Z]) - (u[Z]*v[X]));
  n[Z] = (u[X]*v[Y]) - (u[Y]*v[X]);
  
  double phi = acos((o[X]*n[X])+(o[Y]*n[Y])+(o[Z]*n[Z]));
  double theta = dotProd;
  
  // Rotation matrix
  photon->pol[I] = photon->pol[I];
  photon->pol[Q] = (photon->pol[Q]*cos(2.0*phi)) + (photon->pol[U]*sin(2.0*phi));
  photon->pol[U] = (-photon->pol[Q]*sin(2.0*phi)) + (photon->pol[U]*cos(2.0*phi));
  photon->pol[V] = photon->pol[V];
  
  // Rayleigh Scattering Polarisation Matrix
  photon->pol[I] = (photon->pol[I]*0.5) + (photon->pol[Q]*0.5*cos(2.0*theta)) + (photon->pol[U]*0.5*sin(2.0*theta));
  photon->pol[Q] = (photon->pol[I]*0.5*cos(2.0*theta)) + (photon->pol[Q]*0.5*pow(cos(2.0*theta),2.0)) + (photon->pol[U]*0.5*cos(2.0*theta)*sin(2.0*theta));
  photon->pol[U] = (photon->pol[I]*0.5*sin(2.0*theta)) + (photon->pol[Q]*0.5*cos(2.0*theta)*sin(2.0*theta)) + (photon->pol[V]*0.5*pow(sin(2.0*theta),2.0));
  
  return;
}

void move(Planet *exo,Particle *photon){
  
  double lambda = -log(arcRand(0.0,1.0))/exo->kappa[getLayer(exo,photon->pos[X],photon->pos[Y],photon->pos[Z])];
  //double lambda = pathLength(exo,photon);
  
  photon->lambda = lambda;
  
  for (int i=0; i<3; i++){
    photon->pos[i] += photon->dirVec[i] * lambda;
  }
  
  return;
}

void moveBack(Particle *photon){
  
  for (int i=0; i<3; i++){
    photon->pos[i] -= photon->dirVec[i] * photon->lambda;
  }
  
  return;
}

void observerPol(Particle *photon){
  
  double phi = acos(photon->norm[Y]);
  
  photon->pol[I] = photon->pol[I];
  photon->pol[Q] = (photon->pol[Q]*cos(2.0*phi)) + (photon->pol[U]*sin(2.0*phi));
  photon->pol[U] = (-photon->pol[Q]*sin(2.0*phi)) + (photon->pol[U]*cos(2.0*phi));
  photon->pol[V] = photon->pol[V];
  
  return;
}

/**/ // Records the position of a particle in 3D space.
void dev_recordPos(Particle *photon){
  
  FILE *file;
  file = fopen(outputPath "position.dat","a");
  
  fprintf(file,"%lf %lf %lf\n",photon->pos[X],photon->pos[Y],photon->pos[Z]);

  fclose(file);
}

/**/ // Records what the Planet would look like
void dev_observe(Particle *photon){
  
  FILE *file;
  file = fopen(outputPath "view.dat","a");
  
  double pos[3] = {0.0};
  double alpha = 0.0, omega = 0.0;
  
  for (int i=0; i<3; i++){
    pos[i] = photon->pos[i];
  }
  
  alpha = acos(pos[Z]);
  
  if (pos[X] < 0.0){
    alpha = (2.0*PI) - alpha;
  }

  omega = 45 * (PI/180.0);
  pos[X] = (photon->pos[X]*cos(omega)) - (photon->pos[Z]*sin(omega));
  pos[Z] = (photon->pos[X]*sin(omega)) + (photon->pos[Z]*cos(omega));

  if ((alpha >= 270.0) || (alpha <= 90.0)){
    if (pos[Z] >= 0.0){
      fprintf(file,"%lf %lf %lf %lf %lf %lf\n",pos[X],pos[Y],photon->pol[I],photon->pol[Q],photon->pol[U],photon->pol[V]);
    }
  }
    
  fclose(file);
  
  return;
}

/**/ // Observes if phot dir in right direction.
void dev_recordPol(Particle *photon){
  
  FILE *file;
  file = fopen(outputPath "polarisation.dat","a");
  
  fprintf(file,"%lf %lf %lf %lf %lf %lf %lf %lf\n",photon->pos[X],photon->pos[Y],photon->pos[Z],photon->pol[I],photon->pol[Q],photon->pol[U],photon->pol[V],photon->alpha);
  
  return;
}