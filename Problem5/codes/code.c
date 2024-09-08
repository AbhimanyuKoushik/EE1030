#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "libs/matfun.h"
#include "libs/geofun.h"

void point_gen(FILE *fptr, double **center, double **point_on_circle, int no_rows, int no_col, int num_points) {
    double **output;
    double **dir_vector = Matsub(point_on_circle, center, no_rows, no_col);
    for (int i = 0; i <= num_points; i++) {
        output = Matadd(Matmul(rotMat((i * 2 * M_PI) / num_points), dir_vector, 2, 2, 1), center, no_rows, no_col);
        fprintf(fptr, "%lf,%lf\n", output[0][0], output[1][0]);
        freeMat(output, no_rows);
    }
    freeMat(dir_vector, no_rows);  // Free direction vector
}

int main() {
    int x1 = 2, y1 = -4, x2 = 3, y2 = 8;
    int m = 2, n = 1;
    double **A, **P;

    A = createMat(m, n);
    P = createMat(m, n);

    A[0][0] = x1;
    A[1][0] = y1;
    P[0][0] = x2;
    P[1][0] = y2;

    // Open file to write points
    FILE *fptr;
    fptr = fopen("circ.dat", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Generate points on the circle
    point_gen(fptr, A, P, m, n, 100);

    // Checking equidistant points
    double **reqpoint1, **reqpoint2;
    reqpoint1 = createMat(m, n);
    reqpoint2 = createMat(m, n);

    reqpoint1[0][0] = -10;
    reqpoint1[1][0] = -3;

    reqpoint2[0][0] = -10;
    reqpoint2[1][0] = -5;

    // Check if the point is equidistant from A and P
    if ((Matnorm(Matsub(A, reqpoint1, m, n), m) == Matnorm(Matsub(P, reqpoint1, m, n), m)) &&
        (Matnorm(Matsub(A, reqpoint2, m, n), m) == Matnorm(Matsub(P, reqpoint2, m, n), m))) {
        fprintf(fptr, "Point is equidistant from the given points\n");
    }

    // Close the file
    fclose(fptr);

    // Free all allocated memory
    freeMat(A, m);
    freeMat(P, m);
    freeMat(reqpoint1, m);
    freeMat(reqpoint2, m);

    return 0;
}

