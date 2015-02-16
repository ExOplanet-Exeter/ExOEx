/*==============================================================
----------------------------------------------------------------
                       88                         ad88
                       88                        d8"
                       88                        88
 ,adPPYba,  ,adPPYba,  88,dPPYba,   ,adPPYba,  MM88MMM
a8P_____88  I8[    ""  88P'    "8a  I8[    ""    88
8PP"""""""   `"Y8ba,   88       88   `"Y8ba,     88  88
"8b,   ,aa  aa    ]8I  88       88  aa    ]8I    88  88
 `"Ybbd8"'  `"YbbdP"'  88       88  `"YbbdP"'    88  88
88       88  8b,dPPYba,    ,adPPYba,  ,adPPYba,      88,dPPYba,
88       88  88P'   `"8a  a8"     ""  I8[    ""      88P'    "8a
88       88  88       88  8b           `"Y8ba,       88       88
"8a,   ,a88  88       88  "8a,   ,aa  aa    ]8I  88  88       88
 `"YbbdP'Y8  88       88   `"Ybbd8"'  `"YbbdP"'  88  88       88
----------------------------------------------------------------
  This header file contains Eshwen's completed test functions.
----------------------------------------------------------------
==============================================================*/


//== INCLUDES ==================================================
// Allows the use of everything found in Arc's global.h header.
// If functions are moved into the Arc build then they must
// comply with global.h, so it's useful to keep this in.
#include "../../Arc/globals/global.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>


//== FUNCTION DECLARATIONS =====================================
Particle isoscatterGetDirection(Particle, double);
void isoscatterTest(Particle);


//== FUNCTIONS =================================================
// Main initialises the random number generator and calls the testing functions

int main() {
    time_t t;
    srand((unsigned) time(&t)); // Initialises random number generator
    isoscatterTest(photon);
}

/* Tests isotropic scattering by performing it with N_TEST photons. The sums of
the directional vector components are found. Although ideally being equal to
zero, a 5% tolerance is given.
*/

void isoscatterTest(Particle photon) {
    int i;
    double u_sum = 0, v_sum = 0, w_sum = 0;   // Sum of directional vector components

    for ( i = 0 ; i < N_TEST ; ++i) {
            double phi = 2 * PI * arcRand(0,1);
            isoscatterGetDirection(photon, phi);

            u_sum = u_sum + photon.curPos[X];
            v_sum = v_sum + photon.curPos[Y];
            w_sum = w_sum + photon.curPos[Z];
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

Particle isoscatterGetDirection(Particle photon, phi) {
    photon.curPos[X] = 2 * arcRand(0,1) - 1;
    photon.curPos[Y] = cos(phi) * sqrt( 1 - pow(photon.curPos[Z],2) );
    photon.curPos[Z] = sin(phi) * sqrt( 1 - pow(photon.curPos[Z],2) );

    return photon;
}

#define WAVELENGTH1 91.2 /* Wavelength in nm at which a photon would ionize a
                            hydrogen atom from the electron's ground state */
#define CROSSSECTION_THOMP 6.65E-29 // m^2
#define MASS_HYDROGEN 1.67E-27 // kg

int getOpacity (void) {
	double wavelength, frequency, crosssection;

    printf("Enter the wavelength in nanometres.\n\n");
	scanf("%lg", &wavelength);

	if (wavelength < 91.2 / 0.75 ) {
		printf("\nSorry, but a photon with a wavelength shorter than %lg nm "
               "cause electron transitions in the atom.\n\n", 91.2 / 0.75);
		getOpacity();
	}
	frequency = WAVELENGTH1 / wavelength;

	printf("\nFor a wavelength of %lg nm, the frequency in terms of the Lyman "
           "Limit frequency is %lg.\n\n", wavelength, frequency);

    if (frequency < 0.6) {
            crosssection = CROSSSECTION_THOMP * pow(frequency,4) * ( 1.2654
                                                   + 3.73766 * pow(frequency,2)
                                                   + 8.8127 * pow(frequency,4)
                                                   + 19.1515 * pow(frequency,6)
                                                   + 39.919 * pow(frequency,8)
                                                   + 81.1018 * pow(frequency,10)
                                                   + 161.896 * pow(frequency,12)
                                                   + 319.001 * pow(frequency,14)
                                                   + 622.229 * pow(frequency,16)
                                                   + 1203.82 * pow(frequency,18)
                                                   );
    }
    else if (frequency > 0.6) {
            frequency = (frequency - 0.75) / 0.75;
        crosssection = CROSSSECTION_THOMP * (0.0433056 / pow(frequency,2)) *(1
                                                  - 1.792 * frequency
                                                  - 23.637 * pow(frequency,2)
                                                  - 83.1393 * pow(frequency,3)
                                                  - 244.1453 * pow(frequency,4)
                                                  - 699.473 * pow(frequency,5)
                                                  );
    }
	printf("The Rayleigh scattering cross-section is %lg m^2, or %lg Thompson "
		   "cross-sections. This gives the opacity as %lg m^2/kg.\n",
		   crosssection, crosssection / CROSSSECTION_THOMP,
		   crosssection / MASS_HYDROGEN);
	return 0;
/* Only problem with this is that if you put in an incorrect value of wavelength
and you re-enter a correct value, the function calculates the cross-section and
opacity for both wavelengths that are entered. Not sure yet how I solve this.
*/
}

/*
The following contains old functions I was working on before Christmas. They're
not relevant to what I'm working on now, but may be of use in the future.
*/

/*

//========================= FUNCTION DECLARATIONS =============================
Particle isoscatterPhoton();

//Particle miescatterPhoton();

//=============================== FUNCTIONS ===================================

/*
Single isotropic scattering event for a photon. Can be modified to only
scatter in a certain layer in the exoplanet's atmosphere, once the planet
has been appropriately defined.
*/

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
I NEED TO FINISH AND CHECK THE MIE SCATTERING FUNCTION (AGAINST
http://en.wikipedia.org/wiki/Mon te_Carlo_method_for_photon_transport???), THEN
MAKE A TEST FOR IT.
*/
