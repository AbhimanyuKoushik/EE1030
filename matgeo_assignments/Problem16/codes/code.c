#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "libs/matfun.h"
#include "libs/geofun.h"

typedef struct {
    double v[2];
} Vector2x1;

typedef struct {
    double V[2][2];
    Vector2x1 u;
    double f;
} Parabola;

void parab_x2_4ay_gen(FILE *fptr, Vector2x1 *p1, Vector2x1 *p2, double a, int num_points) {
    double tinit = p1->v[0] / (2 * a);
    double tfinal = p2->v[0] / (2 * a);

    Vector2x1 point;

    if (tfinal > tinit) {
        for (double i = tinit; i <= tfinal + (2.0 / num_points); i += 2.0 / num_points) {
            point.v[0] = 2 * a * i;
            point.v[1] = a * i * i;
            fprintf(fptr, "%lf,%lf\n", point.v[0], point.v[1]);
        }
    } else {
        for (double i = tfinal; i <= tinit + (2.0 / num_points); i += 2.0 / num_points) {
            point.v[0] = 2 * a * i;
            point.v[1] = a * i * i;
            fprintf(fptr, "%lf,%lf\n", point.v[0], point.v[1]);
        }
    }
}

Vector2x1* intersect_of_parab_line(Parabola *parabola, Vector2x1 *point_on_line, Vector2x1 *dir) {
    double m1 = dir->v[0];
    double m2 = dir->v[1];

    double V1 = parabola->V[0][0];
    double V2 = parabola->V[1][0];
    double V3 = parabola->V[0][1];
    double V4 = parabola->V[1][1];

    double u1 = parabola->u.v[0];
    double u2 = parabola->u.v[1];

    double h1 = point_on_line->v[0];
    double h2 = point_on_line->v[1];

    double A = V1 * m1 * m1 + (V2 + V3) * m1 * m2 + V4 * m2 * m2;
    double B = 2 * (m1 * (V1 * h1 + V2 * h2 + u1) + m2 * (V3 * h1 + V4 * h2 + u2));
    double C = h1 * (V1 * h1 + V2 * h2) + h2 * (V3 * h1 + V4 * h2) + 2 * (u1 * h1 + u2 * h2) + parabola->f;

    if (B * B - 4 * A * C < 0) {
        return NULL;
    } else {
        Vector2x1 *intersection = malloc(2 * sizeof(Vector2x1));
        if (B * B - 4 * A * C == 0) {
            double k = -B / (2 * A);
            intersection[0].v[0] = point_on_line->v[0] + k * dir->v[0];
            intersection[0].v[1] = point_on_line->v[1] + k * dir->v[1];
            return intersection;
        } else {
            double k1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
            double k2 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);

            intersection[0].v[0] = point_on_line->v[0] + k1 * dir->v[0];
            intersection[0].v[1] = point_on_line->v[1] + k1 * dir->v[1];

            intersection[1].v[0] = point_on_line->v[0] + k2 * dir->v[0];
            intersection[1].v[1] = point_on_line->v[1] + k2 * dir->v[1];

            return intersection;
        }
    }
}

double area(double (*func)(double), double lower_limit, double upper_limit) {
    double sum = 0;
    for (double i = lower_limit; i <= upper_limit; i += 1e-3) {
        sum += func(i) * 1e-3;
    }
    return sum;
}

double square(double x) {
    return x * x;
}

double identity(double x) {
    return x;
}

int main() {
    Parabola parabola = {
        .V = {{1, 0}, {0, 0}},
        .u = {{0, -0.5}},
        .f = 0
    };

    Vector2x1 point_on_line = {{0, 0}};
    Vector2x1 dir = {{1, 1}};

    Vector2x1 *intersection = intersect_of_parab_line(&parabola, &point_on_line, &dir);

    if (intersection == NULL) {
        printf("No real intersection found.\n");
        return 1;
    }

    Vector2x1 p1 = {{intersection[0].v[0], intersection[0].v[1]}};
    Vector2x1 p2 = {{intersection[1].v[0], intersection[1].v[1]}};

    FILE *fptr = fopen("parab.dat", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    parab_x2_4ay_gen(fptr, &p1, &p2, -parabola.u.v[1] / 2, 200);

    fprintf(fptr, "The area between the given curve and line is %lf", 
            area(identity, 0, 1) - area(square, 0, 1));

    fclose(fptr);

    free(intersection);

    return 0;
}

