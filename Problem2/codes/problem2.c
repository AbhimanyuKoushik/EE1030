#include <stdio.h>

void generate_points_on_line(int n, const char *filename) {
    // Define the coordinates of the two points
    double x1 = 1.0, y1 = 2.0, z1 = 3.0;
    double x2 = 7.0, y2 = 0.0, z2 = -1.0;

    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Generate points on the line
    for (int i = 0; i <= n; i++) {
        double t = (double)i / n;
        double x = x1 + t * (x2 - x1);
        double y = y1 + t * (y2 - y1);
        double z = z1 + t * (z2 - z1);
        
        // Write the point to the file
        fprintf(file, "%.2f, %.2f, %.2f\n", x, y, z);
    }

    // Close the file
    fclose(file);
    printf("Points have been saved to %s\n", filename);
}

int main() {
    int n = 10; // Number of points to generate
    const char *filename = "points.txt";
    generate_points_on_line(n, filename);
    return 0;
}

