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
    double x, y, z, x1, y1, z1;
    // m = no. of rows, n = no. of columns
    int m = 3, n = 1;
    
    // corrdinates of origin and vector which subtends equal angles to all axes (all its components are equal)
    x = 1; y = 1; z = 1;
    x1 = 0; y1 = 0; z1 = 0;
    
    // creating matrices A,B,O
    double **A = createMat(m, n);
    double **B = createMat(m, n);
    double **O = createMat(m, n);
    
    // giving their coordinates
    A[0][0] = x;
    A[1][0] = y;
    A[2][0] = z;
    
    O[0][0]=x1;
    O[1][0]=y1;
    O[2][0]=z1;
    
    // dividing vector A with its norm to make it unit vector
    B = Matscale(A,m,n,1/Matnorm(A,m));
    
    // opening the file
    FILE *fptr;
    fptr = fopen("vector.dat", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    // generating points 
    point_gen(fptr, O, B, 3, 1, 20);
    
    // free matrices
    freeMat(A,m);
    freeMat(B,m);
    freeMat(O,m);
    
    // closing the file
    fclose(fptr);
    return 0;
}