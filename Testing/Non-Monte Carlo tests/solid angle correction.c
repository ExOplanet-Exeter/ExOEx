#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

int main() {
    int m, n;
    double olddata[181][2] = {0};

    FILE *readfile;
    readfile = fopen("ExOExRayleigh05.txt", "r"); // MODIFIED TO SUIT USER

    if ( readfile == NULL ) {
        printf("The file cannot be opened.\n");
        exit(1);
    }

    for (m = 0 ; m < 180 ; ++m) {
        for (n = 0 ; n < 2 ; ++n) {
            fscanf(readfile, "%lg", &olddata[m][n]);
        }
    }
    fclose(readfile);

    double omega;
    double newdata[181][2];
    FILE *outfile;
    outfile = fopen("ExOExRayleigh05new.txt", "w"); // MODIFIED TO SUIT USER

    for (m = 0 ; m < 180 ; ++m) {
        omega = 2 * PI * ( cos(m*PI/180) - cos((m+1)*PI/180) );
        newdata[m][1] = olddata[m][1] / omega;
        fprintf(outfile, "%i %lg\n", m, newdata[m][1] / newdata[0][1]);
    }
    fclose(outfile);

    return 0;
}
