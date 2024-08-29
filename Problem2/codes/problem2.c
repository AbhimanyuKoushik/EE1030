#include <stdio.h>

typedef struct {
    float x;
    float y;
    float z;
} Point3D;

int main() {
    Point3D P1 = {1.0, 2.0, 3.0}; // Example point 1
    Point3D P2 = {7, 0, -1}; // Example point 2
    int numPoints = 10; // Number of points to generate

    FILE *file = fopen("data_points.txt", "w"); // Open file for writing
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    float t;
    Point3D point;

    for (int i = 0; i <= numPoints; i++) {
        t = (float)i / numPoints;
        point.x = P1.x + t * (P2.x - P1.x);
        point.y = P1.y + t * (P2.y - P1.y);
        point.z = P1.z + t * (P2.z - P1.z);

        fprintf(file, "(%.2f, %.2f, %.2f)\n",point.x, point.y, point.z);
    }

    fclose(file); // Close the file
    printf("Points have been saved to points.txt\n");

    return 0;
}

