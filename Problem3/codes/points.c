#include <stdio.h>

int main() {
    FILE *fptr;
    fptr = fopen("triangle_points.txt", "w");

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Number of points to generate along each edge
    int num_points = 20;

    // Generate points on the edge from (0, 4) to (0, 0)
    for (int i = 0; i <= num_points; i++) {
        float x = 0;
        float y = 4.0f * i / num_points;
        fprintf(fptr, "%f %f\n", x, y);
    }

    // Generate points on the edge from (0, 0) to (3, 0)
    for (int i = 0; i <= num_points; i++) {
        float x = 3.0f * i / num_points;
        float y = 0;
        fprintf(fptr, "%f %f\n", x, y);
    }

    // Generate points on the edge from (3, 0) to (0, 4)
    for (int i = 0; i <= num_points; i++) {
        float x = 3.0f - 3.0f * i / num_points;
        float y = 4.0f * i / num_points;
        fprintf(fptr, "%f %f\n", x, y);
    }

    fclose(fptr);
    printf("Points saved to triangle_points.txt\n");
    return 0;
}

