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
    //coordinates of tail and head of vector (1,1,1)^T
    double x, y, z, x1, y1, z1;
    int m = 3, n = 1;
    
    x = 1; y = 1; z = 1;
    x1 = 0; y1 = 0; z1 = 0;
    
    // creating a the vector r
    double **R = createMat(m,n);
    R[0][0] = x;
    R[1][0] = y;
    R[2][0] = z;
    
    // finding the scaling values
    double c1 = (2*sqrt(3))/(Matnorm(R,m));
    double c2 = -(2*sqrt(3))/(Matnorm(R,m));
    
    // creating vectors which satisfy the given conditions
    double **A = createMat(m, n);
    double **B = createMat(m, n);
    double **C = createMat(m, n);
    
    // A is the origin
    A[0][0] = x1;
    A[1][0] = y1;
    A[2][0] = z1;
    
    // multiplying vector r with given scaling factors
    B = Matscale(R,m,n,c1);
    C = Matscale(R,m,n,c2);
    
    // opening the file
    FILE *fptr;
    fptr = fopen("vector.dat", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // generating points 
    point_gen(fptr, A, B, 3, 1, 20);
    point_gen(fptr, A, C, 3, 1, 20);
    
    // checking the length of the vector
    double length = Matnorm(Matsub(B,A,m,n),m);
    
    // free matrices
    freeMat(A,m);
    freeMat(B,m);
    freeMat(C,m);
    freeMat(R,m);
    
    fprintf(fptr, "The length of vector is %lf", length);
    
    // closing the file
    fclose(fptr);
    return 0;
}
