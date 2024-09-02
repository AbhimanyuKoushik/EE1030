#include <stdio.h>

void point_gen(float x1, float y1, float x2, float y2, int num_points) {
    float x, y;
    FILE *fptr;
    fptr = fopen("triangle_points.txt", "a");

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i <= num_points; i++) {
        x = x1 + (x2 - x1) * i / num_points;
        y = y1 + (y2 - y1) * i / num_points;
        fprintf(fptr, "%f %f\n", x, y);
    }

    fclose(fptr);
    printf("Points saved to triangle_points.txt\n");
}

int main() {
    float x1,y1,x2,y2,x3,y3;
    x1=0;y1=4;
    x2=0;y2=0;
    x3=3;y3=0;
    point_gen(x1, y1, x2, y2, 20);
    point_gen(x2, y2, x3, y3, 20);
    point_gen(x3, y3, x1, y1, 20);
    return 0;
}
