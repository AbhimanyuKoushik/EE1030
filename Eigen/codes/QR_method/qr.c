#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "functions.h"

// Function to compute Hessenberg form without the sign adjustment step
double complex **qr_converge(double complex **A, int dim) {
    // Copy the original matrix to prevent modifying A directly
    double complex **H = makehessberg(A, dim);
    double complex **R;
    for(int i = 0; i < 200; i++){
    	double complex **Q = identity(dim);
    	double complex **Q_T = identity(dim);
    	for (int p = 1; p < dim; p++){
		// Calculate theta, sign, and t
		double complex xi = H[p-1][p-1];
		double complex xj = H[p][p-1];
		if(xi==0 && xj==0){
			continue;
		}
		double complex c = conj(xi)/(csqrt(cabs(xi)*cabs(xi)+cabs(xj)*cabs(xj)));
		double complex s = conj(xj)/(csqrt(cabs(xi)*cabs(xi)+cabs(xj)*cabs(xj)));

		double complex **Gi = identity(dim);
		Gi[p-1][p-1] = c;
		Gi[p-1][p] = s;
		Gi[p][p-1] = -conj(s);
		Gi[p][p] = conj(c);
		
		H = Matmul(Gi,H,dim,dim,dim);
		Q_T = Matmul(Q_T,transposeMat(Gi,dim,dim),dim,dim,dim);
    	}
    	H = Matmul(H,Q_T,dim,dim,dim);
    }
    return H;
}

void calcuppereig(double complex **A, int dim) {
    int count = 1;
    for (int i = 0; i < dim; i++) {
        // Check if the element below the diagonal is zero
        if (i < dim - 1 && cabs(A[i + 1][i]) > 1e-12) { // Non-zero entry, handle 2x2 block
            double complex x1 = A[i][i];
            double complex x2 = A[i + 1][i + 1];
            double complex y1 = A[i + 1][i];
            double complex y2 = A[i][i + 1];


            // Coefficients of the quadratic equation: x^2 - (x1+x2)x + (x1x2-y1y2) = 0
            double complex a = 1.0;
            double complex b = -(x1 + x2);
            double complex c = x1 * x2 - y1 * y2;

            // Compute the roots
            double complex eigenvalue1 = (-b + csqrt(b * b - 4.0 * a * c)) / (2.0 * a);
            double complex eigenvalue2 = (-b - csqrt(b * b - 4.0 * a * c)) / (2.0 * a);

            // Print the eigenvalues
            if(cabs(eigenvalue2)>1e-12){
            	printf("Eigenvalue %d: %.9lf + %.9lfi\n", count, creal(eigenvalue1), cimag(eigenvalue1));
            }
            else{
            	printf("Eigenvalue %d: 0.000000000 + 0.000000000i\n", count);
            }
            
            if(cabs(eigenvalue2)>1e-12){
            	printf("Eigenvalue %d: %.9lf + %.9lfi\n", count + 1, creal(eigenvalue2), cimag(eigenvalue2));
            }
            else{
            	printf("Eigenvalue %d: 0.000000000 + 0.000000000i\n", count+1);
            }
            count += 2;

            // Skip the next row since it's part of the 2x2 block
            i++;
        }
        else{ // Diagonal element is an eigenvalue
        	if(cabs(A[i][i])>1e-12){
            		printf("Eigenvalue %d: %.9lf + %.9lfi\n", count, creal(A[i][i]), cimag(A[i][i]));
            	}
            	else{
            		printf("Eigenvalue %d: 0.000000000 + 0.000000000i\n", count);
            	}
            count++;
        }
    }
}

int main() {
    int n = 10; // Example matrix size
    double complex **A = createMat(n, n);
    
    
    A[0][0] = 1.0 + 1.0*I;   A[0][1] = 2.0 + 2.0*I;   A[0][2] = 3.0 + 3.0*I;   A[0][3] = 4.0 + 4.0*I;   A[0][4] = 5.0 + 5.0*I;   A[0][5] = 6.0 + 6.0*I;   A[0][6] = 7.0 + 7.0*I;   A[0][7] = 8.0 + 8.0*I;   A[0][8] = 9.0 + 9.0*I;   A[0][9] = 10.0 + 10.0*I;
    A[1][0] = 11.0 + 11.0*I; A[1][1] = 12.0 + 12.0*I; A[1][2] = 13.0 + 13.0*I; A[1][3] = 14.0 + 14.0*I; A[1][4] = 15.0 + 15.0*I; A[1][5] = 16.0 + 16.0*I; A[1][6] = 17.0 + 17.0*I; A[1][7] = 18.0 + 18.0*I; A[1][8] = 19.0 + 19.0*I; A[1][9] = 20.0 + 20.0*I;
A[2][0] = 21.0 + 21.0*I; A[2][1] = 22.0 + 22.0*I; A[2][2] = 23.0 + 23.0*I; A[2][3] = 24.0 + 24.0*I; A[2][4] = 25.0 + 25.0*I; A[2][5] = 26.0 + 26.0*I; A[2][6] = 27.0 + 27.0*I; A[2][7] = 28.0 + 28.0*I; A[2][8] = 29.0 + 29.0*I; A[2][9] = 30.0 + 30.0*I;
A[3][0] = 31.0 + 31.0*I; A[3][1] = 32.0 + 32.0*I; A[3][2] = 33.0 + 33.0*I; A[3][3] = 34.0 + 34.0*I; A[3][4] = 35.0 + 35.0*I; A[3][5] = 36.0 + 36.0*I; A[3][6] = 37.0 + 37.0*I; A[3][7] = 38.0 + 38.0*I; A[3][8] = 39.0 + 39.0*I; A[3][9] = 40.0 + 40.0*I;
A[4][0] = 41.0 + 41.0*I; A[4][1] = 42.0 + 42.0*I; A[4][2] = 43.0 + 43.0*I; A[4][3] = 44.0 + 44.0*I; A[4][4] = 45.0 + 45.0*I; A[4][5] = 46.0 + 46.0*I; A[4][6] = 47.0 + 47.0*I; A[4][7] = 48.0 + 48.0*I; A[4][8] = 49.0 + 49.0*I; A[4][9] = 50.0 + 50.0*I;
A[5][0] = 51.0 + 51.0*I; A[5][1] = 52.0 + 52.0*I; A[5][2] = 53.0 + 53.0*I; A[5][3] = 54.0 + 54.0*I; A[5][4] = 55.0 + 55.0*I; A[5][5] = 56.0 + 56.0*I; A[5][6] = 57.0 + 57.0*I; A[5][7] = 58.0 + 58.0*I; A[5][8] = 59.0 + 59.0*I; A[5][9] = 60.0 + 60.0*I;
A[6][0] = 61.0 + 61.0*I; A[6][1] = 62.0 + 62.0*I; A[6][2] = 63.0 + 63.0*I; A[6][3] = 64.0 + 64.0*I; A[6][4] = 65.0 + 65.0*I; A[6][5] = 66.0 + 66.0*I; A[6][6] = 67.0 + 67.0*I; A[6][7] = 68.0 + 68.0*I; A[6][8] = 69.0 + 69.0*I; A[6][9] = 70.0 + 70.0*I;
A[7][0] = 71.0 + 71.0*I; A[7][1] = 72.0 + 72.0*I; A[7][2] = 73.0 + 73.0*I; A[7][3] = 74.0 + 74.0*I; A[7][4] = 75.0 + 75.0*I; A[7][5] = 76.0 + 76.0*I; A[7][6] = 77.0 + 77.0*I; A[7][7] = 78.0 + 78.0*I; A[7][8] = 79.0 + 79.0*I; A[7][9] = 80.0 + 80.0*I;
A[8][0] = 81.0 + 81.0*I; A[8][1] = 82.0 + 82.0*I; A[8][2] = 83.0 + 83.0*I; A[8][3] = 84.0 + 84.0*I; A[8][4] = 85.0 + 85.0*I; A[8][5] = 86.0 + 86.0*I; A[8][6] = 87.0 + 87.0*I; A[8][7] = 88.0 + 88.0*I; A[8][8] = 89.0 + 89.0*I; A[8][9] = 90.0 + 90.0*I;
A[9][0] = 91.0 + 91.0*I; A[9][1] = 92.0 + 92.0*I; A[9][2] = 93.0 + 93.0*I; A[9][3] = 94.0 + 94.0*I; A[9][4] = 95.0 + 95.0*I; A[9][5] = 96.0 + 96.0*I; A[9][6] = 97.0 + 97.0*I; A[9][7] = 98.0 + 98.0*I; A[9][8] = 99.0 + 99.0*I; A[9][9] = 100.0 + 100.0*I;

    double complex **qr = qr_converge(A,n);	
    calcuppereig(qr,n);
    
    freeMat(A, n);
    freeMat(qr, n);
    return 0;
}
