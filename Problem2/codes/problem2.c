#include <stdio.h>

// Structure to represent a point in 3D space
typedef struct {
    float x;
    float y;
    float z;
} Point3D;

// Function to generate points between two given points and write them to a file
void generatePoints(Point3D p1, Point3D p2, int numPoints, FILE *file) {
    fprintf(file, "Points between (%.2f, %.2f, %.2f) and (%.2f, %.2f, %.2f):\n", p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
    for (int i = 0; i <= numPoints; i++) {
        float t = (float)i / numPoints;
        Point3D p;
        p.x = (1 - t) * p1.x + t * p2.x;
        p.y = (1 - t) * p1.y + t * p2.y;
        p.z = (1 - t) * p1.z + t * p2.z;
        fprintf(file, "(%.2f, %.2f, %.2f)\n", p.x, p.y, p.z);
    }
    fprintf(file, "\n");
}

int main() {
    // Define the points
    Point3D p1 = {-2, 3, 5};
    Point3D p2 = {1, 2, 3};
    Point3D p3 = {7, 0, -1};

    // Number of intermediate points to generate
    int numPoints = 10;

    // Open a file to save the points
    FILE *file = fopen("data_points.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Generate points between each pair of points and write to the file
    generatePoints(p1, p2, numPoints, file);
    generatePoints(p2, p3, numPoints, file);
    generatePoints(p3, p1, numPoints, file);

    // Close the file
    fclose(file);

    printf("Data points saved to data_points.txt\n");

    return 0;
}

