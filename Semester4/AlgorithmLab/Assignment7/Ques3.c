#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct {
    double x, y;
} Point;

int compareX(const void* a, const void* b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x > p2->x) - (p1->x < p2->x);
}

int compareY(const void* a, const void* b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y > p2->y) - (p1->y < p2->y);
}

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

void findClosest1D(Point pts[], int n) {
    qsort(pts, n, sizeof(Point), compareX);
    double min_dist = DBL_MAX;
    Point p1, p2;

    for (int i = 0; i < n - 1; i++) {
        double d = fabs(pts[i].x - pts[i+1].x);
        if (d < min_dist) {
            min_dist = d;
            p1 = pts[i];
            p2 = pts[i+1];
        }
    }
    printf("Closest 1D Pair: (%.2f) and (%.2f) with distance %.2f\n", p1.x, p2.x, min_dist);
}

double bruteForce2D(Point pts[], int n, Point *bestP1, Point *bestP2) {
    double min = DBL_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double d = dist(pts[i], pts[j]);
            if (d < min) {
                min = d;
                *bestP1 = pts[i];
                *bestP2 = pts[j];
            }
        }
    }
    return min;
}

void findClosest2D(Point pts[], int n) {
    Point p1, p2;
    double min_dist = bruteForce2D(pts, n, &p1, &p2);
    printf("Closest 2D Pair: (%.2f, %.2f) and (%.2f, %.2f) with distance %.2f\n", 
            p1.x, p1.y, p2.x, p2.y, min_dist);
}

int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    Point *pts = (Point*)malloc(n * sizeof(Point));
    printf("Enter coordinates (x y) for each point:\n");
    for (int i = 0; i < n; i++) {
        scanf("%le %le", &pts[i].x, &pts[i].y);
    }

    printf("\n--- Results ---\n");
    findClosest1D(pts, n);
    
    findClosest2D(pts, n);

    free(pts);
    return 0;
}