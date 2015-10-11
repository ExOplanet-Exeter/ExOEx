#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define N_ROWS 37000 // Number of rows in ExOEx's .dat file
#define N_COLS 7 // Number of columns in ExOEx's .dat file

int main() {
    int m = 0, n = 0; // Indices for array for mapping data
    double rayleighData[N_ROWS][N_COLS] = {0}; /* Array to store ExOEx's data.
    Laid out with columns of incoming x,y,z, outgoing x,y,z, and weight. */
    double resultantData[181] = {0}; // Array to store useful data

    FILE *readfile;
    readfile = fopen("ray.dat", "r");

    if ( readfile == NULL ) {
        printf("The file cannot be opened.\n");
        exit(1);
    }
    for (m = 0 ; m < N_ROWS ; ++m) {
        for (n = 0 ; n < N_COLS ; ++n) {
            fscanf(readfile, "%lg", &rayleighData[m][n]);
        }
    } // Maps the .dat file and stores it in an array within the program
    for (m = 0 ; m < N_ROWS ; ++m) {
        int i = round ( 180 / PI *
                acos( (rayleighData[m][0]*rayleighData[m][3] +
                       rayleighData[m][1]*rayleighData[m][4] +
                       rayleighData[m][2]*rayleighData[m][5] ) ) );
        /* Calculates the scattering angle using dot product of the incoming
        and outgoing angles, then puts it in degrees and rounds it */
        resultantData[i] = resultantData[i] + rayleighData[m][6];
        // Adds the weight to the corresponding element of resultantData
    }
    FILE *outfile;
    outfile = fopen("resultant_data.dat", "w");

    int j;
    for (j = 0 ; j < 180 ; ++j)
        fprintf(outfile, "%i %lg\n", j, resultantData[j]);
        // Writes resultantData to a file with angle as reference
    fclose(outfile);
   return 0;
}
