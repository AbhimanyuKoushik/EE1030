#include <stdio.h>
#include "matfun.h"
#include <math.h>

void point_gen(float **A, float **B, int num_points) {
    FILE *fptr;
    fptr = fopen("triangle_points.txt", "a");

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 1; i < num_points; i++) {
    	double **output=Matsec(A,B,2,(float) i/num_points;
        fprintf(fptr, "%f %f\n", output[0], output[1]);
    }

    fclose(fptr);
    printf("Points saved to triangle_points.txt\n");
}

int main() {
    float A[2],B[2],C[2];
    A=[0,4];B=[3,0];C=[0,0];
    point_gen(A,B,20);
    point_gen(B,C,20);
    point_gen(C,A,20);
    return 0;
}
