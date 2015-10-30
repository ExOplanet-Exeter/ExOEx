#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define N_ROWS 180
#define N_COLS 5 // 2 columns just for intensity, 5 if including polarization

int main() {
    int m, n;
    double olddata[N_ROWS][N_COLS] = {0};

    FILE *readfile;
    readfile = fopen("ExOExRayleigh10.txt", "r"); // MODIFIED TO SUIT USER

    if ( readfile == NULL ) {
        printf("The file cannot be opened.\n");
        exit(1);
    }

    for (m = 0 ; m < N_ROWS ; ++m) {
        for (n = 0 ; n < N_COLS ; ++n) {
            fscanf(readfile, "%lg", &olddata[m][n]);
        }
    }
    fclose(readfile);

    double omega;
    double newdata[N_ROWS][N_COLS];
    FILE *outfile;
    outfile = fopen("ExOExRayleigh10new.txt", "w"); // MODIFIED TO SUIT USER

    for (m = 0 ; m < N_ROWS ; ++m) {
        omega = 2 * PI * ( cos(m*PI/180) - cos((m+1)*PI/180) );
        newdata[m][1] = olddata[m][1] / omega;
        if (N_COLS > 2) {
            newdata[m][2] = olddata[m][2] / omega;
            newdata[m][3] = olddata[m][3] / omega;
            newdata[m][4] = olddata[m][4] / omega;
            fprintf(outfile, "%i %lg %lg %lg %lg\n", m, newdata[m][1] / newdata[0][1],
                    newdata[m][2], newdata[m][3], newdata[m][4]);
        }
        else
            fprintf(outfile, "%i %lg\n", m, newdata[m][1] / newdata[0][1]);
    }
    fclose(outfile);

    return 0;
}
