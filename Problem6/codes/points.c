#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "libs/matfun.h"
#include "libs/geofun.h"

void point_gen(FILE *fptr, double **A, double **B, int num_points) {
    for (int i = 0; i <= num_points; i++) {
        double **output = Matsec(A, B, 2, (double) i / num_points);
        fprintf(fptr, "%lf,%lf\n", output[0][0], output[1][0]);
        freeMat(output,2);
    }
}

int main() {
    double x1, y1, x2, y2;
//    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
    x1 = 0; y1 = 2*sqrt(5);
    x2 = -2*sqrt(5); y2 = 0;
    int m = 2, n = 1;
    double **A = createMat(m, n);
    double **B = createMat(m, n);

    A[0][0] = x1;
    A[1][0] = y1;
    B[0][0] = x2;
    B[1][0] = y2;

    FILE *fptr;
    fptr = fopen("points.dat", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    point_gen(fptr, A, B, 20);
    
     // Free all allocated memory
    freeMat(A,m);
    freeMat(B,m);
    fclose(fptr);
    return 0;
    
}

