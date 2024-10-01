#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "libs/matfun.h"
#include "libs/geofun.h"

void circ_2Dgen(FILE *fptr, double **center, double radius, int no_rows, int no_col, int num_points) {
    double **output;
    double **unitx = createMat(no_rows, no_col);  // Allocate memory for unitx
    unitx[0][0] = 1;
    unitx[0][1] = 0;

    double **dir_vector = Matscale(unitx, no_rows, no_col, radius);
    for (int i = 0; i <= num_points; i++) {
        output = Matadd(Matmul(rotMat((i * 2 * M_PI) / num_points), dir_vector, 2, 2, 1), center, no_rows, no_col);
        fprintf(fptr, "%lf,%lf\n", output[0][0], output[1][0]);
        freeMat(output, no_rows);
    }
    freeMat(dir_vector, no_rows);  // Free direction vector
    freeMat(unitx, no_rows);       // Free unit vector
}


double** centre_rad_gen_with_points_on_circ_and_normtodiameter(double **point1, double **point2, double **norm_to_dia, int c, int no_rows, int no_cols){
	double **coeffmatrix = createMat(3,3);
	double **tosolve = createMat(3,1);
	double **solution = createMat(3,1);
	
	coeffmatrix[0][0] = Matscale(point1,no_rows,no_cols,2)[0][0];
	coeffmatrix[1][0] = Matscale(point2,no_rows,no_cols,2)[0][0];
	coeffmatrix[2][0] = norm_to_dia[0][0];
	coeffmatrix[0][1] = Matscale(point1,no_rows,no_cols,2)[1][0];
	coeffmatrix[1][1] = Matscale(point2,no_rows,no_cols,2)[1][0];
	coeffmatrix[2][1] = norm_to_dia[1][0];
	coeffmatrix[0][2] = 1;
	coeffmatrix[1][2] = 1;
	coeffmatrix[2][2] = 0;
	
	tosolve[0][0] = -pow(Matnorm(point1, no_rows),2);
	tosolve[1][0] = -pow(Matnorm(point2, no_rows),2);
	tosolve[2][0] = -c;
	
	printf("The coeff matrix is\n");
	printMat(coeffmatrix,3,3);
	
	printf("The to solve matrix is\n");
	printMat(tosolve,3,1);
	
	solution = Matmul(Matinv(coeffmatrix,3),tosolve,3,3,1);
	
	printf("The inverse of coeff Matrix is\n");
	printMat(Matinv(coeffmatrix,3),3,3);	
	
	printf("The coeffmatrix*inv(coeffmatrix) is\n");
	printMat(Matmul(coeffmatrix,Matinv(coeffmatrix,3),3,3,3),3,3);
	
	freeMat(tosolve,3);
	
	return solution;
}

int main() {
    int x1 = 2, y1 = 3, x2 = 4, y2 = 5;
    int m = 2, n = 1;
    double **A, **B, **normal;

    A = createMat(m, n);
    B = createMat(m, n);
    normal = createMat(m,n);

    A[0][0] = x1;
    A[1][0] = y1;
    B[0][0] = x2;
    B[1][0] = y2;
    normal[0][0] = -4;
    normal[1][0] = 1;
    
    double **cent = createMat(m,n);
    double f;
    
    double **solution = centre_rad_gen_with_points_on_circ_and_normtodiameter(A, B, normal, -3, m, n);
    cent[0][0] = -solution[0][0];
    cent[1][0] = -solution[1][0];
    f = solution[2][0];

    double radius = sqrt(Matnorm(cent, 2) * Matnorm(cent, 2) - f);

    printf("centre is (%lf,%lf) and radius is %lf\n", cent[0][0], cent[1][0], radius);


    // Open file to write points
    FILE *fptr;
    fptr = fopen("circ.dat", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    circ_2Dgen(fptr,cent,radius,m,n,100);
    
    // Close the file
    fclose(fptr);

    // Free all allocated memory
    freeMat(A, m);
    freeMat(B, m);
    freeMat(normal, m);
    freeMat(cent, m);

    return 0;
}

