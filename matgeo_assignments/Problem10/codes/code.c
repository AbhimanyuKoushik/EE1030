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

double** sidelength_vector_gen_2anglesperimeter(double angleB, double angleC, double perimeter) {

    // Solving the matrix equation in form of Ax=b with x=inv(A)b
    double **coeff = createMat(3, 3);
    double **b = createMat(3, 1);
    double **lengths = createMat(3, 1);
    double **sidematrix = createMat(3, 1);
    
    //Assigning the values
    coeff[0][0] = 1;
    coeff[1][0] = 1;
    coeff[2][0] = 1;
    coeff[0][1] = -1;
    coeff[1][1] = cos(angleC);
    coeff[2][1] = cos(angleB);
    coeff[0][2] = 0;
    coeff[1][2] = sin(angleC);
    coeff[2][2] = -sin(angleB);
    b[0][0] = 1;
    b[1][0] = 0;
    b[2][0] = 0;
    sidematrix = Matscale(b, 3, 1, perimeter);
    
    //Solving the equation and getting side lengths of the triangle
    lengths = Matmul(Matinv(coeff, 3), sidematrix, 3, 3, 1);
    
    // Free allocated memory
    freeMat(b, 3);
    freeMat(sidematrix, 3);
    
    return lengths;
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
    double sideAB, sideBC, sideCA;
    double **length;
    
    length = sidelength_vector_gen_2anglesperimeter(M_PI/3, M_PI/4, 12);
    sideBC = length[0][0];
    sideCA = length[1][0];
    sideAB = length[2][0];

    // Generate triangle points
    twoDtriangle_gen(sideAB, sideBC, sideCA, "triangle.dat");
    
    return 0;
}
