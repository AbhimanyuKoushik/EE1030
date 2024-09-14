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
    double x, y, z, x1, y1, z1, x2, y2, z2, x3, y3, z3;
//    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
    int m = 3, n = 1;
    
    x = 1; y = 1; z = 1;
    
    double **X = createMat(m,n);
    X[0][0] = x;
    X[1][0] = y;
    X[2][0] = z;
    double c1 = (2*sqrt(3))/(Matnorm(X,m));
    double c2 = -(2*sqrt(3))/(Matnorm(X,m));
    
    x1 = 0; y1 = 0; z1 = 0;
    x2 = c1*x; y2 = c1*y; z2 = c1*z;
    x3 = c2*x; y3 = c2*y; z3 = c2*z;
    

    double **A = createMat(m, n);
    double **B = createMat(m, n);
    double **C = createMat(m, n);

    A[0][0] = x1;
    A[1][0] = y1;
    A[2][0] = z1;
    B[0][0] = x2;
    B[1][0] = y2;
    B[2][0] = z2;
    C[0][0] = x3;
    C[1][0] = y3;
    C[2][0] = z3;

    FILE *fptr;
    fptr = fopen("vector.dat", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    point_gen(fptr, A, B, 3, 1, 20);
    point_gen(fptr, A, C, 3, 1, 20);
    double length = Matnorm(Matsub(B,A,m,n),m);
    
    freeMat(A,m);
    freeMat(B,m);
    freeMat(C,m);
    freeMat(X,m);
    
    fprintf(fptr, "The length of vector is %lf", length);
    fclose(fptr);
    return 0;
}
