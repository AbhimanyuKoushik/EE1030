#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

double complex **createMat(int m, int n);
double complex **Matadd(double complex **a, double complex **b, int m, int n);
double complex **Matscale(double complex **a, int m, int n, double complex k);
double Matnorm(double complex **a, int m);
void printMat(double complex **p, int m, int n);
double complex **transposeMat(double complex **a, int m, int n);
double complex Matdot(double complex **a, double complex **b, int m);
double complex **Matunit(double complex **a, int m);
double complex **Matmul(double complex **a, double complex **b, int m, int n, int p);
double complex **Matcol(double complex **a, int m, int col);
double complex **Matsub(double complex **a, double complex **b, int m, int n);
double complex **identity(int dim);
double complex **copyMat(double complex **src, int m, int n);
void freeMat(double complex **a, int m);

double complex **createMat(int m, int n) {
    double complex **a = (double complex **)malloc(m * sizeof(*a));
    for (int i = 0; i < m; i++) {
        a[i] = (double complex *)malloc(n * sizeof(*a[i]));
    }
    for(int i=0;i<m;i++){
    	for(int j=0;j<n;j++){
    		a[i][j] = 0;
    	}
    }
    return a;
}

double complex **Matadd(double complex **a, double complex **b, int m, int n) {
    double complex **c = createMat(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

double complex **Matscale(double complex **a, int m, int n, double complex k) {
    double complex **c = createMat(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = k * a[i][j];
        }
    }
    return c;
}

double Matnorm(double complex **a, int m) {
    double norm = 0;
    for (int i = 0; i < m; i++) {
        norm += creal(a[i][0]) * creal(a[i][0]) + cimag(a[i][0]) * cimag(a[i][0]);
    }
    return sqrt(norm);
}

void printMat(double complex **p, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("(%lf + %lfi) ", creal(p[i][j]), cimag(p[i][j]));
        }
        printf("\n");
    }
}

double complex **transposeMat(double complex **a, int m, int n) {
    double complex **c = createMat(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i][j] = conj(a[j][i]);
        }
    }
    return c;
}

double complex Matdot(double complex **a, double complex **b, int m) {
    double complex result = 0;
    for (int i = 0; i < m; i++) {
        result += a[i][0] * conj(b[i][0]);
    }
    return result;
}

double complex **Matunit(double complex **a, int m) {
    double complex **c = createMat(m, 1);
    double norm = Matnorm(a, m);
    for (int i = 0; i < m; i++) {
        c[i][0] = a[i][0] / norm;
    }
    return c;
}

double complex **Matmul(double complex **a, double complex **b, int m, int n, int p) {
    double complex **c = createMat(m, p);
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < p; k++) {
            c[i][k] = 0;
            for (int j = 0; j < n; j++) {
                c[i][k] += a[i][j] * b[j][k];
            }
        }
    }
    return c;
}

double complex **Matcol(double complex **a, int m, int col) {
    double complex **b = createMat(m, 1);
    for (int i = 0; i < m; i++) {
        b[i][0] = a[i][col];
    }
    return b;
}

double complex **Matsub(double complex **a, double complex **b, int m, int n) {
    double complex **c = createMat(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

double complex **identity(int dim) {
    double complex **A = createMat(dim, dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            A[i][j] = (i == j) ? 1 + 0 * I : 0 + 0 * I;
        }
    }
    return A;
}

double complex **copyMat(double complex **src, int m, int n) {
    double complex **dest = createMat(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
    return dest;
}

void freeMat(double complex **a, int m) {
    for (int i = 0; i < m; i++) {
        free(a[i]);
    }
    free(a);
}

