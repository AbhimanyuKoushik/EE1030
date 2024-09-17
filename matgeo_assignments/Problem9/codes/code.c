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
        fprintf(fptr, "%lf,%lf\n", output[0][0], output[1][0]);
        freeMat(output,no_rows);
    }
}

void twoDtriangle_gen(double sideAB, double sideBC, double sideCA, char filename[]) {
    double xA, yA, xB, yB, xC, yC;

    // Correct formula for angle A
    double angleA = acos(((sideAB * sideAB) + (sideCA * sideCA) - (sideBC * sideBC)) / (2 * sideAB * sideCA));

    xA = 0; yA = 0;
    xB = sideAB; yB = 0;
    xC = cos(angleA) * sideCA; yC = sin(angleA) * sideCA;

    int m = 2, n = 1;

    // Open the file for writing
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;  // Return early if file cannot be opened
    }

    // Create matrices for vertices
    double **A = createMat(m, n);
    double **B = createMat(m, n);
    double **C = createMat(m, n);

    A[0][0] = xA;
    A[1][0] = yA;
    B[0][0] = xB;
    B[1][0] = yB;
    C[0][0] = xC;
    C[1][0] = yC;

    // Generate points along the triangle's edges
    point_gen(fptr, A, B, m, n, 20);
    point_gen(fptr, B, C, m, n, 20);
    point_gen(fptr, C, A, m, n, 20);

    // Free allocated memory
    freeMat(A, m);
    freeMat(B, m);
    freeMat(C, m);

    // Close the file
    fclose(fptr);
}

int main() {
    double sideAB, sideBC, var1_sideCA, var2_sideCA, var3_sideCA, var4_sideCA;
    
    // Input the sides of the triangle
    sideAB = 5;
    sideBC = 1.5;
    var1_sideCA = 3.6;
    var2_sideCA = 4.1;
    var3_sideCA = 3.8;
    var4_sideCA = 3.4;

    // Generate triangle points
    twoDtriangle_gen(sideAB, sideBC, var1_sideCA, "triangle1.dat");
    twoDtriangle_gen(sideAB, sideBC, var2_sideCA, "triangle2.dat");
    twoDtriangle_gen(sideAB, sideBC, var3_sideCA, "triangle3.dat");
    twoDtriangle_gen(sideAB, sideBC, var4_sideCA, "triangle4.dat");

    return 0;
}
