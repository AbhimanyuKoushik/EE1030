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
    double x1, y1, x2, y2, x3, y3;
//    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
    x1 = 0; y1 = 4;
    x2 = 0; y2 = 0;
    x3 = 3; y3 = 0;

    int m = 2, n = 1;
    double **A = createMat(m, n);
    double **B = createMat(m, n);
    double **C = createMat(m, n);

    A[0][0] = x1;
    A[1][0] = y1;
    B[0][0] = x2;
    B[1][0] = y2;
    C[0][0] = x3;
    C[1][0] = y3;

    FILE *fptr;
    fptr = fopen("triangle_points.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    point_gen(fptr, A, B, 20);
    point_gen(fptr, B, C, 20);
    point_gen(fptr, C, A, 20);

    double **s_ab = Matsub(A, B, m, n);
    double **s_bc = Matsub(B, C, m, n);
    double **s_ca = Matsub(C, A, m, n);
    double **a_ba = Matsub(B, A, m, n);
    double sideAB = Matnorm(s_ab, m);
    double sideBC = Matnorm(s_bc, m);
    double sideCA = Matnorm(s_ca, m);
    double perimeter = sideAB + sideBC + sideCA;
    
     // Free all allocated memory
    freeMat(A,m);
    freeMat(B,m);
    freeMat(C,m);
    freeMat(s_ab,m);
    freeMat(s_bc,m);
    freeMat(s_ca,m);
    freeMat(a_ba,m);

    fprintf(fptr, "Perimeter of the triangle is %lf\n", perimeter);
    fclose(fptr);
    return 0;
    
}

