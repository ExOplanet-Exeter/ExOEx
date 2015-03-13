#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define N_ROWS 1000
#define N_COLS 1000
#define RADIUS_PLANET 1
#define DIST_STAR 10    // Distance from planet to star

/*
- FIX BUG THAT'S GIVING ME A SLIGHTLY LARGER VISIBLE AREA FOR PHASE ANGLES > 180^o.
- ADD UNITS TO PARAMETERS LIKE INTENSITY, FLUX, AREA AND DISTANCE?
- INCLUDE ISOTROPIC AND RAYLEIGH SCATTERING (FIGURE OUT HOW TO READ IN SPECIFIC VALUES FOR THE
  H-FUNCTION ETC. FOR A GIVEN MU (THAT'S ROUNDED TO COINCIDE WITH VALUES IN THE TABLES.
*/

typedef struct variables {
    double areaGrid[N_ROWS][N_COLS];    // array containing surface area elements of planet
    double obsPhaseangle;               // Angle between observer and planet relative to star
    double obsDistance;                 // Distance from observer to planet
    double obsDistance_x;               // x-coordinate of observer's position
    double obsDistance_y;               // y-coordinate of observer's position
    int i;                              // 'i' is a theta designation
    int j;	                            // 'j' is a phi designation
    double theta;                       // theta increases with row value in areaGrid
    double phi;                         // phi with column value in areaGrid
    double delta_theta;                 // theta increment between successive cells
    double delta_phi;                   // phi increment between successive cells
	double mu;							// cosine of the angle between star and observer
    double intensity_element;           // Intensity of radiation reflected by a surface area element
    double area_visible;                // Amount of surface area illuminated and visible to observer
    double flux_received;               // Total flux received by the observer
} Variables;

Variables *newvariables(void) {
    Variables *A = malloc(sizeof *A);
    return A;
}

void populategrid (Variables *);
void getAngles (Variables *);
void getVisibleArea (Variables *);
void getMu (Variables *, double, double, double);
void getReceivedFlux (Variables *);
double conductLambert (Variables *);
double conductIso (Variables *);
double conductRayleigh (Variables *);

int main () {
	int choice;

	Variables *A = newvariables(); // Initializes structure

	printf("Enter a phase angle (in degrees) and distance (in units of the exoplanet's radius) "
           "between the observer and exoplanet.\n");

    scanf("%lg %lg", &A->obsPhaseangle, &A->obsDistance);
    if ( A->obsPhaseangle < 0 || A->obsPhaseangle > 360 ) {
        printf("Please enter a value between 0 and 360 for the phase angle.\n");
        main();
    }
    else if ( A->obsDistance < 1 ) {
        printf("Please enter an observation distance of 1 or greater.\n");
        main();
    }
    else {
        A->obsPhaseangle = A->obsPhaseangle * PI / 180;     // Converts phase angle to radians
        A->obsDistance = A->obsDistance * RADIUS_PLANET;    // Scales observation distance
        A->obsDistance_x = A->obsDistance * cos(A->obsPhaseangle);
        A->obsDistance_y = A->obsDistance * sin(A->obsPhaseangle);
    }

    printf("For Lambert scattering, enter '1'.\n"
		   "For isotropic scattering, enter '2'.\n"
		   "For Rayleigh scattering, enter '3'.\n");

	scanf("%i", &choice);
	if (choice < 1 || choice > 3) {
		printf("Number is invalid, please choose again.\n");
		main();
	}
	else if (choice == 1)
		conductLambert(A);
	else if (choice == 2)
		conductIso(A);
	else if (choice == 3)
		conductRayleigh(A);
}

void populategrid (Variables *A) {

	double area_total = 0;          // Initializes the total area to zero
	A->delta_theta = PI / N_ROWS;
	A->delta_phi = 2 * PI / N_COLS;

	for (A->i = 0; A->i < N_ROWS; ++A->i) {
		for (A->j = 0; A->j < N_COLS; ++A->j) {
			getAngles(A);
			A->areaGrid[A->i][A->j] = pow(RADIUS_PLANET,2) * sin(A->theta) * A->delta_theta *
                                      A->delta_phi; //Finds the area of the element
			area_total = area_total + A->areaGrid[A->i][A->j];
		}
	}
	double area_expected = 4 * PI * pow(RADIUS_PLANET,2);

	printf("The expected area of the planet (4.pi.R^2) is %g, and the summation of all the area "
           "elements in our grid is %g. This gives a discrepancy (as a fraction) of %g.\n",
           area_expected, area_total, fabs(area_total/area_expected - 1) );
}

void getAngles (Variables *A) {
	A->theta = (A->i + 1) * A->delta_theta;
	A->phi = (A->j + 1) * A->delta_phi;
} // Calculates the spherical angles for the corresponding surface area element

void getVisibleArea (Variables *A) {
	A->area_visible = A->area_visible + A->areaGrid[A->i][A->j];
}

void getMu (Variables *A, double x, double y, double modPos_element) {
	A->mu = cos( acos(-x / modPos_element) +
				 acos((x*A->obsDistance_x + y*A->obsDistance_y) / (modPos_element * A->obsDistance)) );
/* acos(mu) is the angle between the star and observer, which is the angle between the star and the
   normal of the area element plus the angle between the normal of the area element and the observer.*/
}

void getReceivedFlux (Variables *A) {
	A->flux_received = A->flux_received + (A->intensity_element * A->mu * A->areaGrid[A->i][A->j]);
}

double conductLambert (Variables *A) {
	populategrid(A);

	double x, y, z;         // Cartesian components of position of area element
	double modPos_element;  // Modulus of position of area element
	A->area_visible = 0;    // Initializes visible area to zero
	A->flux_received = 0;   // Initializes total flux to zero

    for (A->i = 0; A->i < N_ROWS; ++A->i) {
		for (A->j = 0; A->j < N_COLS; ++A->j) {
			getAngles(A);
            x = RADIUS_PLANET * sin(A->theta) * cos(A->phi);
            y = RADIUS_PLANET * sin(A->theta) * sin(A->phi);
            z = RADIUS_PLANET * cos(A->theta);
            modPos_element = sqrt(x*x + y*y + z*z);

            if ( -x / modPos_element > 0 && (x*A->obsDistance_x + y*A->obsDistance_y) /
											(modPos_element * A->obsDistance) > 0 ) {
/* The star is lying on the -x-axis: the first condition determines whether the angle between the
   normal of the area element and star is < 90 degrees, if so it's illuminated. The second condition
   tests whether the angle between the normal of the area element and the observer is < 90 degrees, if
   so it's visible. */
				getVisibleArea(A);
				getMu(A, x, y, modPos_element);
                A->intensity_element = A->mu;
				// Should also multiply by incident flux and albedo, but they're just scaling factors
                getReceivedFlux(A);
            }
		}
    }
    A->flux_received = A->flux_received / pow(A->obsDistance,2);
    // Normalizes the total flux

    printf("The total surface area of the planet that is both illuminated and visible is %g (equal to "
           "%g.pi.R^2), and the total flux density received by the observer is %g.\n", A->area_visible,
           A->area_visible / (PI * RADIUS_PLANET), A->flux_received);

	return 0;
}

double conductIso (Variables *A) {
    populategrid(A);
    // DO CALCULATIONS
	return 0;
}

double conductRayleigh (Variables *A) {
    populategrid(A);
    // DO CALCULATIONS
	return 0;
}
