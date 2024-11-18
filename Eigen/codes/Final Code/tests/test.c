#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "functions.h"

int main(){
    int n;
    scanf("%d", &n);
    double complex** matrix = createMat(n, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            double a, b;
            scanf("%lf %lf", &a, &b);
            matrix[i][j] = CMPLX(a, b);
        }
    }
    eigenvalues(matrix, n);
}
