#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "libs/matfun.h"
#include "libs/geofun.h"

void point_gen(FILE *fptr, double **A, double **B, int no_rows, int no_cols, int num_points) {
    for (double i = 0; i <= num_points; i++) {
        double **output = Matadd(A, Matscale(Matsub(B,A,no_rows,no_cols),no_rows,no_cols,(double)i/num_points), no_rows, no_cols);
        fprintf(fptr, "%lf,%lf,%lf\n", output[0][0], output[1][0], output[2][0]);
        freeMat(output,no_rows);
    }
}

int main() {
    double x1, y1, z1, x2, y2, z2, x3, y3, z3;
//    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
    x1 = 1; y1 = 2; z1 = 3;
    x2 = 7; y2 = 0; z2 = -1;
    
    int m = 3, n = 1;
    double **A = createMat(m, n);
    double **B = createMat(m, n);

    A[0][0] = x1;
    A[1][0] = y1;
    A[2][0] = z1;
    B[0][0] = x2;
    B[1][0] = y2;
    B[2][0] = z2;

    FILE *fptr;
    fptr = fopen("points.dat", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    point_gen(fptr, A, B, 3, 1, 20);
    
    freeMat(A,m);
    freeMat(B,m);
    
    fclose(fptr);
    return 0;
}
