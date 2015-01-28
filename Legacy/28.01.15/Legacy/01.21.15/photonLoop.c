
/*
  This function is where the bulk of calculation occures
  modeling the photons travelling onto, and then within the
  exoplanet
*/

//================================================== INCLUDES ==
#include <stdio.h>
#include <math.h>

#include "global.h"
#include "utilities.h"                                          // Utility functions (random gen etc)


//=================================================== DEFINES ==
#define starDist 5.0                                            // Distance photons are emitted


//======================================= FUNCTION PROTOTYPES == 
Particle intialisePhoton(Particle,int);
Particle stellarEmission(Particle,double);
double mapToExo(Particle,Planet);
double jumpLength(Planet);
Particle inject(Particle,Planet);
double getRho(Particle);
double calcAlpha(Particle);
Particle prepareToJump(Particle);

//====================================================== MAIN == 
Particle photonLoop(Planet exo, int n) {
  //if (DEBUG)
  //printf(ACYAN "\nStage: Photon Loop\n" ARESET);

  // Declerations
  Particle photon;                                              // Creation of a photon struct, filled in and passed to main
  
  // Simulation functions
  photon = intialisePhoton(photon,n);                           // Photon parameters nullified
  photon = stellarEmission(photon,exo.radius);                  // Photons sent to star surface
  photon.pos[Z] = mapToExo(photon,exo);                         // Photons 'mapped' to exoplanet atmosphere
  photon = inject(photon,exo);                                  // Photon travels in before any scattering
  
  //while(getRho(photon) < exo.radius){
    
    //}

  photon.alpha = 1.0;
  photon.alpha = calcAlpha(photon);                             // Calculate angle of emission

  return photon;                                                // Return the filled out photon data back to main
}


//================================================= FUNCTIONS == 
// Initialise a new photons parameters
Particle intialisePhoton(Particle photon, int n) {
  photon.identity  = n;                                         // Id set equal to 'n' to differentiate photons

  photon.pos[X]    = 0.0;
  photon.pos[Y]    = 0.0;
  photon.pos[Z]    = 0.0;

  photon.oldPos[X] = 0.0;
  photon.oldPos[Y] = 0.0;
  photon.oldPos[Z] = 0.0;

  photon.alpha     = 0.0;

  return photon;
}

// Move photon to random point on stellar surface
Particle stellarEmission(Particle photon, double radius) {
  double rho = radius+1.0;                                      // Deliberately set to be larger than radius
  
  while (rho > radius) {                                        // Repeates until photon is generated in the right place
    photon.pos[X] = arcRand(-radius,radius);
    photon.pos[Y] = arcRand(-radius,radius);
    rho = sqrt(pow(photon.pos[X],2.0)+pow(photon.pos[Y],2.0));
  }

  photon.pos[Z] = starDist;                                     // Photon is put at stellar surface (ultimately meaningless)
  return photon;
}

// Map the photon to the outer atmosphere
double mapToExo(Particle photon, Planet exo) {
  double rho,h;
  
  rho = sqrt(pow(photon.pos[X],2.0)+pow(photon.pos[Y],2.0));    // Determne rho
  h = sqrt(pow(exo.radius,2.0)-pow(rho,2.0));                   // Height of atmosphere is a function of rho
  
  return h;
}

// Determines a jump length dependant on optical depth
double jumpLength(Planet exo) {
  return -log(arcRand(0.0,1.0))*exo.tao;                        // Random number used to determine jump length
}

// Determines the photons distance from planet centre
double getRho (Particle photon) {
  return sqrt(pow(photon.pos[X],2.0)+pow(photon.pos[Y],2.0)+pow(photon.pos[Z],2.0));
}


// Calculates the angle of emission 'alpha'
double calcAlpha(Particle photon) {
  double i,j,k,mag;

  i = photon.pos[X] - photon.oldPos[X];
  j = photon.pos[Y] - photon.oldPos[Y];
  k = photon.pos[Z] - photon.oldPos[Z];
  
  mag = sqrt(pow(i,2.0)+pow(j,2.0)+pow(k,2.0));
  
  i = i / mag;
  j = j / mag;
  k = k / mag;

  return acos(-1.0*k);                                           // Effectively returns the dot product between angle
                                                                 // angle and unit vector between planet and star
}


//
Particle inject(Particle photon, Planet exo) {
  photon = prepareToJump(photon);

  photon.pos[Z] = photon.pos[Z] - jumpLength(exo);

  return photon;
}


// Set photon.oldPos[somethign] to photon.Pos[something]
Particle prepareToJump(Particle photon) {
  photon.oldPos[X] = photon.pos[X];
  photon.oldPos[Y] = photon.pos[Y];
  photon.oldPos[Z] = photon.pos[Z];

  return photon;
}
