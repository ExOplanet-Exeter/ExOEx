#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "global.h"
#include "utilities.h"

#define PI 3.14159265359
#define N_TEST 10000         // Number of photons used in testing functions

//========================= STRUCTURE DEFINITIONS =============================

typedef struct photondirection {
    double u;
    double v;
    double w;
    double phi;
    double L_scat;  // Scattering length
    /* The following variables are components for Mie scattering:
    double u_prime;
    double v_prime;
    double w_prime;
    double theta;
    double g;       // Asymmetry/anisotropy factor */
} Photon_Direction;

Photon_Direction *isotropicscatter(void) {
    Photon_Direction *p = malloc(sizeof *p);
    return p;
}

/*Photon_Direction *miescatter(void) {
    Photon_Direction *p = malloc(sizeof *p);
    return p;
}*/

//========================= FUNCTION DECLARATIONS =============================

double getPhi();
double getScatteringLength();

void isoscatterTest();
Particle isoscatterPhoton();
double isoscatterGetDirection();

//Particle miescatterPhoton();

//=============================== FUNCTIONS ===================================

// Main initialises the random number generator and calls the testing functions

int main() {
    time_t t;
    srand((unsigned) time(&t)); // Initialises random number generator
    isoscatterTest();
}

/* Tests isotropic scattering by performing it with N_TEST photons. The sums of
the directional vector components are found. iAlthough ideally being equal to
zero, a 5% tolerance is given.
*/

void isoscatterTest() {
    Photon_Direction *p = isotropicscatter();

    int i;
    double u_sum = 0, v_sum = 0, w_sum = 0;   // Sum of directional vector components

    for ( i = 0 ; i < N_TEST ; ++i) {
            getPhi(p);
            isoscatterGetDirection(p);

            u_sum = u_sum + p->u;
            v_sum = v_sum + p->v;
            w_sum = w_sum + p->w;
    }
    if (fabs(u_sum / N_TEST) < 0.05 &&
        fabs(v_sum / N_TEST) < 0.05 &&
        fabs(w_sum / N_TEST) < 0.05   )       // Allows a tolerance of 5%
        printf("Isotropic scattering: WORKING!\n");
    else {
        printf("Istropic scattering: FAILED!\n"
               "Please review the code to determine the problem.\n");
        exit(1);
    }
}

/*
Single isotropic scattering event for a photon. Can be modified to only
scatter in a certain layer in the exoplanet's atmosphere, once the planet
has been appropriately defined.
*/

Particle isoscatterPhoton(Particle photon, Planet exo) {
    Photon_Direction *p = isotropicscatter();

    photon.oldPos[X] = photon.pos[X];
    photon.oldPos[Y] = photon.pos[Y];
    photon.oldPos[Z] = photon.pos[Z];
    /*
    ^^^ Takes values of photon's current positon and puts them in place of the
    values for its old position, so that its new position can be inserted after
    the scatter.
    */

    getPhi(p);
    isoscatterGetDirection(p);
    getScatteringLength(p, exo);

    photon.pos[X] = photon.oldPos[X] + (p->L_scat * p->u);
    photon.pos[Y] = photon.oldPos[Y] + (p->L_scat * p->v);
    photon.pos[Z] = photon.oldPos[Z] + (p->L_scat * p->w);

    return photon;
}

double getPhi(Photon_Direction *p) {
    p->phi = 2 * PI * arcRand(0,1);
}

double getScatteringLength(Photon_Direction *p, Planet exo) {
    p->L_scat = -log(arcRand(0.0,1.0))*exo.tao;
}

double isoscatterGetDirection(Photon_Direction *p) {
    p->w = 2 * arcRand(0,1) - 1;
    p->u = cos(p->phi) * sqrt( 1 - p->w * p->w);
    p->v = sin(p->phi) * sqrt( 1 - p->w * p->w);
}

/*
Single Mie scattering event for a photon using the Henyey-Greenstein
approximation. Like isotropic, it can be modified to work in certain layers of
the exoplanet's atmosphere.
*/

/*Particle miescatterPhoton(Particle photon, Planet exo) {
    Photon_Direction *p = miescatter();

    getScatteringLength(L_scat, exo);
    getPhi(p);

    p->u = photon.pos[X] - photon.oldPos[X];
    p->v = photon.pos[Y] - photon.oldPos[Y];
    p->w = photon.pos[Z] - photon.oldPos[Z]; // Finding the initial direction of travel of photon (need to divide by previous scattering length)?

    p->theta = acos( 1 / (2 * exo.g) * ( 1 + exo.g * exo.g - pow( ( (1 - exo.g * exo.g) / 1 - exo.g + 2*exo.g*arcRand(0,1) ) , 2 ) ) );
    // ^^^ Assumes 'g' is defined in the 'planet' structure

    if (p->w == 1) {
        p->u_prime = sin(p->theta) * cos(p->phi);
        p->v_prime = sin(p->theta) * sin(p->phi);
        p->w_prime = cos(p->theta);
    }
    else if (p->w == -1) {
        p->u_prime = sin(p->theta) * cos(p->phi);
        p->v_prime = -sin(p->theta) * sin(p->phi);
        p->w_prime = -cos(p->theta);
    }
    else {
        p->u_prime = sin(p->theta) * (p->u * p->w * cos(p->phi) - p->v * sin(p->phi)) / sqrt(1 - p->w * p->w) + p->u * cos(p->theta);
        p->v_prime = sin(p->theta) * (p->v * p->w * cos(p->phi) + p->u * sin(p->phi)) / sqrt(1 - p->w * p->w) + v * cos(p->theta);
        p->w_prime = -sqrt(1 - p->w * p->w) * sin(p->theta) * cos(p->phi) + p->w * cos(p->theta);
    }

    photon.pos[X] = photon.oldPos[X] + (p->L_scat * p->u_prime);
    photon.pos[Y] = photon.oldPos[Y] + (p->L_scat * p->v_prime);
    photon.pos[Z] = photon.oldPos[Z] + (p->L_scat * p->w_prime);

    return photon;
}*/

/*
ALL OF THE MIE SCATTERING STUFF IS ONLY INCLUDED AS COMMENTS. I NEED TO EITHER
NOT USE POINTERS AND FIGURE OUT HOW TO DO SAY iso.u, iso.v, ETC., OR FIND SOME
WAY TO DIFFERENTIATE BETWEEN THE POINTERS USED FOR MIE AND ISOTROPIC SCATTERING
BUT ALSO RECONCILE THE STRUCTURES BEING PASSSED TO COMMON FUNCTIONS LIKE getPhi
OR getScatteringLength. I ALSO NEED TO FINISH AND CHECK THE MIE SCATTERING
FUNCTION (AGAINST http://en.wikipedia.org/wiki/Monte_Carlo_method_for_photon_transport???),
THEN MAKE A TEST FOR MIE SCATTERING, MAKE THE RAYLEIGH SCATTERING FUNCTION AND
THEN A TEST FOR THAT.
*/
