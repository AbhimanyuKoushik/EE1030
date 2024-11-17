#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "functions.h"

// Function to compute Hessenberg form with Rayleigh Quotient Shift
double complex **qr_converge_rayleigh(double complex **A, int dim) {
    double complex **H = makehessberg(A, dim); // Reduce to Hessenberg form
    double complex sigma;
    double tol = 1e-10; // Convergence tolerance

    for (int m = dim; m > 1; m--) {
        int iter = 0;

        while (iter < 20*dim) { // Limit iterations to 500
            iter++;
            sigma = H[m-1][m-1]; // Rayleigh shift

            // Shifted matrix: H - sigma * I
            double complex **sigmaI = Matscale(identity(dim), dim, dim, sigma);
            double complex **H_shifted = Matsub(H, sigmaI, dim, dim);

            // Initialize Q_T (accumulated orthogonal transformations)
            double complex **Q_T = identity(dim);

            for (int p = 1; p < m; p++) {
                double complex xi = H_shifted[p-1][p-1];
                double complex xj = H_shifted[p][p-1];

                if (cabs(xj) < tol) {
                    continue;
                }

                // Compute Givens rotation parameters
                double complex c = conj(xi)/(csqrt(cabs(xi)*cabs(xi)+cabs(xj)*cabs(xj)));
		double complex s = conj(xj)/(csqrt(cabs(xi)*cabs(xi)+cabs(xj)*cabs(xj)));
		
                // Create Givens rotation matrix Gi
                double complex **Gi = identity(dim);
                Gi[p-1][p-1] = c;
                Gi[p-1][p] = s;
                Gi[p][p-1] = -conj(s);
                Gi[p][p] = conj(c);

                // Apply Gi to H_shifted and accumulate in Q_T
                H_shifted = Matmul(Gi, H_shifted, dim, dim, dim);
                Q_T = Matmul(Q_T, transposeMat(Gi, dim, dim), dim, dim, dim);

                freeMat(Gi, dim);
            }

            // Update H: H = Q_T^H * H_shifted * Q_T
            H = Matmul(H_shifted, Q_T, dim, dim, dim);
            H = Matadd(H, sigmaI, dim, dim); // Add back the shift

            // Free temporary matrices
            freeMat(sigmaI, dim);
            freeMat(H_shifted, dim);
            freeMat(Q_T, dim);

            // Check for convergence
            //converged = 1;
                if (cabs(H[m-1][m-2]) > tol) {
                    continue;
                }
                else{
                	break;
                }
        }

        if (iter >= 1000) {
            printf("Warning: QR algorithm did not converge for m = %d after 1000 iterations\n", m);
        } else {
            printf("Converged for m = %d after %d iterations\n", m, iter);
        }
        printf("This is H for m=%d\n",m);
        printMat(H,dim,dim);
        printf("\n");
    }

    return H;
}



int main() {
    int n = 3; // Example matrix size
    double complex **A = createMat(n, n);
    
    A[0][0] = 1 + 0*I;
    A[0][1] = 2 + 0*I;
    A[0][2] = 3 + 0*I;

    A[1][0] = 2 + 0*I;
    A[1][1] = 3 + 0*I;
    A[1][2] = 4 + 0*I;

    A[2][0] = 3 + 0*I;
    A[2][1] = 4 + 0*I;
    A[2][2] = 1 + 0*I;
    
    printf("Original Matrix:\n");
    printMat(A, n, n);
    printf("\n");
    
    double complex **qr = qr_converge_rayleigh(A, n);
    calcuppereig(qr,n);

    freeMat(A, n);
    freeMat(qr, n);
    return 0;
}
