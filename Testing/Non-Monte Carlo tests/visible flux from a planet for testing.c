#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define N_ROWS 500
#define N_COLS 500
#define RADIUS_PLANET 1
#define DIST_STAR 10    // Distance from planet to star

typedef struct variables {
    double areaGrid[N_ROWS][N_COLS];    /* Array containing surface area
										 elements of planet */
	double albedo;						// Single scattering albedo
    double phaseAngle;                  /* Angle between observer and planet
										 relative to star set so maximum flux
										 is at a phase angle of zero */
    int i;                              // 'i' is a theta designation
    int j;	                            // 'j' is a phi designation
    double theta;                       /* zenith angle of surface element,
                                        increases with row value in areaGrid */
    double phi;                         /* azimuthal angle of surface element,
                                        increases w/ column value in areaGrid*/
    double delta_theta;                 /* theta increment between successive
										 cells */
    double delta_phi;                   /* phi increment between successive
										 cells */
	double element_x;					/* x-component of position of area
										 element */
	double element_y;					/* y-component of position of area
										 element */
	double mu_in;						/* Cosine of the[incident]angle between
										 the star and normal to area element */
    double azimuthal_in;                // Azimuthal angle for incident light
	double H_muin;						// H-function value for mu_in
	double psi_muin;                    // psi-function value for mu_in
	double phi_muin;                    // phi-function value for mu_in
	double chi_muin;                    // chi-function value for mu_in
	double zeta_muin;                   // zeta-function value for mu_in
	double H1_muin;                     // H1-function value for mu_in
	double H2_muin;                     // H2-function value for mu_in
	double mu_out;						/* Cosine of the [outgoing/scattering]
										 angle between the normal to the area
										 element and observer */
    double azimuthal_out;               // Azimuthal angle for scattered light
	double H_muout;						// H-function value for mu_out
    double psi_muout;                   // psi-function value for mu_out
	double phi_muout;                   // phi-function value for mu_out
	double chi_muout;                   // chi-function value for mu_out
	double zeta_muout;                  // zeta-function value for mu_out
	double H1_muout;                    // H1-function value for mu_out
	double H2_muout;                    // H2-function value for mu_out
	double Hvalues[21][10];				// Array to store H-function values
	double Multifunctionvalues[21][6];  /* Array to store the values from
                                         multiple function in a single array */
    double intensity_element;           /* Intensity of radiation received by a
										 surface area element */
    double flux_received;               // Total flux received by the observer
} Variables;

Variables *newvariables(void) {
    Variables *A = malloc(sizeof *A);
    return A;
}

void makearrays (Variables *, int);
void gridcalculations (Variables *, int);
void getAngles (Variables *);
void getCartesianPosition (Variables *);
void getMus (Variables *, int);
void getReceivedFlux (Variables *);
void conductLambert (Variables *);
void conductIso (Variables *);
void conductRayleigh (Variables *);

int main () {
	int choice;

	Variables *A = newvariables(); // Initializes structure

    printf("For Lambert scattering, enter '1'.\n"
		   "For isotropic scattering, enter '2'.\n"
		   "For Rayleigh scattering, enter '3'.\n");

	scanf("%i", &choice);
	if (choice < 1 || choice > 3) {
		printf("Number is invalid, please choose again.\n");
		main();
	}
	else if (choice == 2 || choice == 3) {
        printf("Enter an albedo between 0.05 and 1.\n");
        /* An albedo of < 0.05 rounds down to 0 in later calculations, yielding
		 no reflected radiation */
        scanf("%lg", &A->albedo);
        if (A->albedo < 0.05 || A->albedo > 1) {
			printf("Albedo is in the wrong range, please choose again.\n");
			main();
        }
        else
            makearrays(A, choice);
	}
	// Main calculations begin from now
    int G;

    FILE *outfile;
    outfile = fopen("flux_array.txt","w"); // opens file for writing

    for (G = 0 ; G <= 180 ; ++G) {
        printf("Phase angle = %i\n", G); // Just used to track progress
        A->phaseAngle = (180 - G) * PI / 180;
        // Sets phase angle and converts from degrees to radians
        gridcalculations(A, choice);

        double normalizer;
        if (G == 0)
            normalizer = A->flux_received;
        // gets the flux at zero phase angle to normalize phase curve
        fprintf(outfile, "%i %g\n", G, A->flux_received / normalizer);
    }
    fclose(outfile);
	return 0;
}

void makearrays(Variables *A, int choice) {
    int m, n; // Indices for arrays

    if (choice == 2) {
        FILE *readfile;
        readfile = fopen("H-function_values_reduced.txt", "r");

        if ( readfile == NULL ) {
            printf("The file cannot be opened.\n");
            exit(1);
        }
        for (m = 0 ; m < 21 ; ++m) {
            for (n = 0 ; n < 10 ; ++n) {
                fscanf(readfile, "%lg", &A->Hvalues[m][n]);
            }
        } /* Maps the table in H-function_values_reduced.txt and stores the
		   information in a 2D array */
        fclose(readfile);
        /* It's easier to open the .txt file and copy the information to an
		 array that can be called repeatedly, rather than having to open the
		 .txt file each time in order to read-in specific values. */
    }
    else if (choice == 3) {
        FILE *readfile;
        readfile = fopen("Multi-function_values.txt","r");

        if ( readfile == NULL ) {
            printf("The file cannot be opened.\n");
            exit(1);
        }
        for (m = 0 ; m < 21 ; ++m) {
            for (n = 0 ; n < 6; ++n) {
                fscanf(readfile, "%lg", &A->Multifunctionvalues[m][n]);
            }
        } /* Maps the table in Multi-function_tables.txt and stores the
		   information in a 2D array */
    }
}

void gridcalculations (Variables *A, int choice) {
	A->delta_theta = PI / N_ROWS;
	A->delta_phi = 2 * PI / N_COLS;

	A->flux_received = 0;   // Initializes total flux to zero

	for (A->i = 0; A->i < N_ROWS; ++A->i) {
		for (A->j = 0; A->j < N_COLS; ++A->j) {
			getAngles(A);
			A->areaGrid[A->i][A->j] = pow(RADIUS_PLANET,2) * sin(A->theta) *
			A->delta_theta * A->delta_phi;
			//Finds the area of the element
			getCartesianPosition(A);
			getMus(A, choice);

			if ( A->mu_in > 0 && A->mu_out > 0 ) {
				/* The first condition determines whether the incicent angle is
				 < 90 degrees, if so it's illuminated. The second condition
				 tests whether the outgoing (scattering) angle is < 90 degrees,
				 if so it's visible. */
				if (choice == 1)
					conductLambert(A);
				else if (choice == 2)
					conductIso(A);
				else if (choice == 3)
					conductRayleigh(A);

				getReceivedFlux(A);
			}
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
} // Gets x- and y-Cartesian components of position of area element

void getMus (Variables *A, int choice) {
    A->mu_in = -A->element_x / RADIUS_PLANET;
    /* acos(mu_in) is the incident angle, which is the angle between the
	 star and the normal to the surface element. This forces the star to lie
	 on the -x-axis. */
    A->mu_out = ( A->element_x*cos(A->phaseAngle) +
                  A->element_y*sin(A->phaseAngle) ) / (RADIUS_PLANET);
    /* acos(mu_out) is the angle between the normal to the surface element
	 and the observer */
    if (choice == 2 || choice == 3) {
        A->mu_in = round(A->mu_in * 20.0) / 20.0;
        A->mu_out = round(A->mu_out * 20.0) / 20.0;
        /* Rounds mu_in and mu_out to the nearest 0.05 to seek correct values
		 in Hvalues and Multifunctionvalues arrays */
    }
}

void getReceivedFlux (Variables *A) {
	A->flux_received = A->flux_received + (A->intensity_element * A->mu_out *
                                           A->areaGrid[A->i][A->j]);
	/* Should divide by the square of the observer's distance, but it's just a
	 scaling factor */
}

void conductLambert (Variables *A) {
	A->intensity_element = A->mu_in;
	/* Should also multiply by incident flux and albedo but they're just
	scaling factors */
} // Gets intensity from an area element due to Lambertian scattering

void conductIso (Variables *A) {
	A->albedo = round(A->albedo * 10.0) / 10.0;
	// Rounds albedo to the nearest 0.1 to seek correct values in Hvalues array

	A->H_muin = A->Hvalues[(long) (A->mu_in * 20)][(long) (A->albedo * 10) - 1];
	A->H_muout = A->Hvalues[(long) (A->mu_out* 20)][(long) (A->albedo * 10) - 1];

    A->intensity_element = A->mu_in / (A->mu_in + A->mu_out) *
                           A->H_muin * A->H_muout;
    // Should multiply by albedo * flux / 4, but they're scaling factors
} // Gets intensity from an area element due to isotropic scattering

void conductRayleigh (Variables *A) {
    A->azimuthal_in = atan( tan(A->phi) / cos(A->theta) );
    A->azimuthal_out = atan( sin(A->phaseAngle) * cos(A->theta) /
							( A->mu_in*A->mu_out - cos(A->phaseAngle) ) );

    A->psi_muin = A->Multifunctionvalues[(long) (A->mu_in * 20)][0];
    A->psi_muout = A->Multifunctionvalues[(long) (A->mu_out * 20)][0];
	// Psi function values are in column 0 of Multifunctionvalues
    A->phi_muin = A->Multifunctionvalues[(long) (A->mu_in * 20)][1];
    A->phi_muout = A->Multifunctionvalues[(long) (A->mu_out * 20)][1];
	// Phi function values are in column 1 of Multifunctionvalues
    A->chi_muin = A->Multifunctionvalues[(long) (A->mu_in * 20)][2];
    A->chi_muout = A->Multifunctionvalues[(long) (A->mu_out * 20)][2];
	// Chi function values are in column 2 of Multifunctionvalues
    A->zeta_muin = A->Multifunctionvalues[(long) (A->mu_in * 20)][3];
    A->zeta_muout = A->Multifunctionvalues[(long) (A->mu_out * 20)][3];
	// Zeta function values are in column 3 of Multifunctionvalues
    A->H1_muin = A->Multifunctionvalues[(long) (A->mu_in * 20)][4];
    A->H1_muout = A->Multifunctionvalues[(long) (A->mu_out * 20)][4];
	// H1 function values are in column 4 of Multifunctionvalues
    A->H2_muin = A->Multifunctionvalues[(long) (A->mu_in * 20)][5];
    A->H2_muout = A->Multifunctionvalues[(long) (A->mu_out * 20)][5];
    // H2 function values are in column 5 of Multifunctionvalues

    A->intensity_element = (A->mu_in / (A->mu_in + A->mu_out)) * (

    (A->psi_muin + A->chi_muin)*(A->psi_muout + A->chi_muout) +

    2*(A->phi_muin + A->zeta_muin)*(A->phi_muout + A->zeta_muout) -

    4*A->mu_in*A->mu_out*sqrt( (1-pow(A->mu_in,2))*(1-pow(A->mu_out,2)) )*
    A->H1_muin*A->H1_muout*cos(A->azimuthal_in - A->azimuthal_out) +

    (1 - pow(A->mu_in,2))*(1 - pow(A->mu_out,2))*A->H2_muin*A->H2_muout*
    cos( 2*(A->azimuthal_in - A->azimuthal_out) ) );
} // Gets intensity from an area element due to Rayleigh scattering
