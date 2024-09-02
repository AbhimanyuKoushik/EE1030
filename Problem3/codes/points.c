#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "libs/matfun.h"
#include "libs/geofun.h"

void point_gen(double **A, double **B, int num_points) {
    FILE *fptr;
    fptr = fopen("triangle_points.txt", "a");
	
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i <= num_points; i++) {
        double **output = Matsec(A, B, 2, (double) i / num_points);
        fprintf(fptr, "%lf,%lf\n", output[0][0], output[1][0]);
        // Free the memory allocated by Matsec (if necessary)
    }

    fclose(fptr);
    printf("Points saved to triangle_points.txt\n");
}

int main() {
    double x1, y1, x2, y2, x3, y3;
//    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
	x1=0;y1=4;
	x2=0,y2=0;
	x3=3;y3=0;

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

    point_gen(A, B, 20);
    point_gen(B, C, 20);
    point_gen(C, A, 20);

    return 0;
}

