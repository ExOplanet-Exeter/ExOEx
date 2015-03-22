#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define N_ROWS 750
#define N_COLS 750
#define RADIUS_PLANET 1
#define DIST_STAR 10    // Distance from planet to star

/*
- INCLUDE ISOTROPIC AND RAYLEIGH SCATTERING (FIGURE OUT HOW TO READ IN SPECIFIC
  VALUES FOR THE H-FUNCTION ETC. FOR A GIVEN MU (THAT'S ROUNDED TO COINCIDE
  WITH VALUES IN THE TABLES).
*/

typedef struct variables {
    double areaGrid[N_ROWS][N_COLS];    /* Array containing surface area
                                           elements of planet */
    double obsPhaseangle;               /* Angle between observer and planet
                                           relative to star set so maximum flux
                                           is at a phase angle of zero */
    double obsDistance;                 // Distance from observer to planet
    double obsDistance_x;               // x-coordinate of observer's position
    double obsDistance_y;               // y-coordinate of observer's position
    int i;                              // 'i' is a theta designation
    int j;	                            // 'j' is a phi designation
    double theta;                       /* theta increases with row value in
                                           areaGrid */
    double phi;                         // phi with column value in areaGrid
    double delta_theta;                 /* theta increment between successive
                                           cells */
    double delta_phi;                   /* phi increment between successive
                                           cells */
	double element_x;					/* x-component of position of area
                                           element */
	double element_y;					/* y-component of position of area
	                                       element */
	double element_z;					/* z-component of position of area
	                                       element */
	double mu_in;						/* Cosine of the angle between star and
	                                       area normal */
	double mu_out;						/* Cosine of the angle between the area
                                           normal and observer */
    double intensity_element;           /* Intensity of radiation received by a
                                           surface area element */
    double area_visible;                /* Amount of surface area illuminated
                                           and visible to observer */
    double flux_received;               // Total flux received by the observer
} Variables;

Variables *newvariables(void) {
    Variables *A = malloc(sizeof *A);
    return A;
}

void populategrid (Variables *);
void getAngles (Variables *);
void getCartesianPosition (Variables *);
void getVisibleArea (Variables *);
void getMus (Variables *);
void getReceivedFlux (Variables *);
void conductLambert (Variables *);
void conductIso (Variables *);
void conductRayleigh (Variables *);

int main () {
	int choice;

	Variables *A = newvariables(); // Initializes structure

	A->obsDistance = 2 * RADIUS_PLANET;
	// Arbitrary observation distance, makes no difference to result

    printf("For Lambert scattering, enter '1'.\n"
		   "For isotropic scattering, enter '2'.\n"
		   "For Rayleigh scattering, enter '3'.\n");

	scanf("%i", &choice);
	if (choice < 1 || choice > 3) {
		printf("Number is invalid, please choose again.\n");
		main();
	}
	else {
		int G;

		FILE *outfile;
		outfile = fopen("flux_array.txt","w"); // opens file for writing

		for (G = 0 ; G <= 180 ; ++G) {
			printf("phase angle = %i\n", G);
			A->obsPhaseangle = (180 - G) * PI / 180;
			// Sets phase angle and converts from degrees to radians
			A->obsDistance_x = A->obsDistance * cos(A->obsPhaseangle);
			A->obsDistance_y = A->obsDistance * sin(A->obsPhaseangle);
			if (choice == 1)
				conductLambert(A);
			else if (choice == 2)
                conductIso(A);
            else if (choice == 3)
                conductRayleigh(A);

			double normalizer;
			if (G == 0)
				normalizer = A->flux_received;
				// gets the flux at zero phase angle to normalize phase curve

			fprintf(outfile, "%i %g\n", G, A->flux_received / normalizer);
		}
		fclose(outfile);
	}
	return 0;
}

void populategrid (Variables *A) {

	double area_total = 0;          // Initializes the total area to zero
	A->delta_theta = PI / N_ROWS;
	A->delta_phi = 2 * PI / N_COLS;

	for (A->i = 0; A->i < N_ROWS; ++A->i) {
		for (A->j = 0; A->j < N_COLS; ++A->j) {
			getAngles(A);
			A->areaGrid[A->i][A->j] = pow(RADIUS_PLANET,2) * sin(A->theta) *
                                      A->delta_theta * A->delta_phi;
			//Finds the area of the element
			area_total = area_total + A->areaGrid[A->i][A->j];
		}
	}
}

void getAngles (Variables *A) {
	A->theta = (A->i + 1) * A->delta_theta;
	A->phi = (A->j + 1) * A->delta_phi;
} // Calculates the spherical angles for the corresponding surface area element

void getCartesianPosition (Variables *A) {
	A->element_x = RADIUS_PLANET * sin(A->theta) * cos(A->phi);
	A->element_y = RADIUS_PLANET * sin(A->theta) * sin(A->phi);
	A->element_z = RADIUS_PLANET * cos(A->theta);
} // Gets Cartesian components of position of area element


void getVisibleArea (Variables *A) {
	A->area_visible = A->area_visible + A->areaGrid[A->i][A->j];
}

void getMus (Variables *A) {
	A->mu_in = -A->element_x / RADIUS_PLANET;
	/* acos(mu_in) is the incident angle, which is the angle between the star
	   and the normal to the surface element */
	A->mu_out = (A->element_x*A->obsDistance_x + A->element_y*A->obsDistance_y)
              / (RADIUS_PLANET * A->obsDistance);
	/* acos(mu_out) is the angle between the normal to the surface element and
	   the observer */
}

void getReceivedFlux (Variables *A) {
	A->flux_received = A->flux_received + (A->intensity_element * A->mu_out *
                                           A->areaGrid[A->i][A->j]);
	/* Should divide by the square of the observer's distance, but it's just a
	   scaling factor */
}

void conductLambert (Variables *A) {
	populategrid(A);

	A->area_visible = 0;    // Initializes visible area to zero
	A->flux_received = 0;   // Initializes total flux to zero

    for (A->i = 0; A->i < N_ROWS; ++A->i) {
		for (A->j = 0; A->j < N_COLS; ++A->j) {
			getAngles(A);
			getCartesianPosition(A);

            if ( -A->element_x / RADIUS_PLANET > 0 &&
                (A->element_x*A->obsDistance_x + A->element_y*A->obsDistance_y)
                 / (RADIUS_PLANET * A->obsDistance) > 0 ) {
/* The star is lying on the -x-axis: the first condition determines whether the
   angle between the normal of the area element and star is < 90 degrees, if so
   it's illuminated. The second condition tests whether the angle between the
   normal of the area element and the observer is < 90 degrees, if so it's
   visible. */
				getVisibleArea(A);
				getMus(A);
                A->intensity_element = A->mu_in;
				/* Should also multiply by incident flux and albedo but they're
				   just scaling factors */
                getReceivedFlux(A);
            }
		}
    }
	printf("The visible illuminated area is %g.pi.R^2.\n",
           A->area_visible / (PI * pow(RADIUS_PLANET,2)) );
}

void conductIso (Variables *A) {
    populategrid(A);
    // DO CALCULATIONS
}

void conductRayleigh (Variables *A) {
    populategrid(A);
    // DO CALCULATIONS
}
