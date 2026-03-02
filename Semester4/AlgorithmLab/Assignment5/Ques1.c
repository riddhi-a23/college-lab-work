#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *P; //parent array of size n
    int *R; //rank array of size n 
    int n; 
} DisjointSet;

DisjointSet* createSet(int n) {
    DisjointSet* ds = (DisjointSet*)malloc(sizeof(DisjointSet));
    ds->n = n;
    ds->P = (int*)malloc(n * sizeof(int));
    ds->R = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        ds->P[i] = i; 
        ds->R[i] = 0;
    }
    return ds;
}

// Find with Path Compression
int find(DisjointSet* ds, int x) {
    if (ds->P[x] != x) {
        ds->P[x] = find(ds, ds->P[x]); // Path compression
    }
    return ds->P[x];
}

// Union by Rank
void unionSets(DisjointSet* ds, int x, int y) {
    int rootX = find(ds, x);
    int rootY = find(ds, y);

    if (rootX != rootY) {
        // Attach smaller rank tree under higher rank tree
        if (ds->R[rootX] > ds->R[rootY]) {
            ds->P[rootY] = rootX;
        } else if (ds->R[rootX] < ds->R[rootY]) {
            ds->P[rootX] = rootY;
        } else {
            ds->P[rootY] = rootX;
            ds->R[rootX]++; // Increase rank if heights are the same
        }
        printf("Union successful: %d and %d merged.\n", x, y);
    } else {
        printf("Elements %d and %d are already in the same set.\n", x, y);
    }
}

// Free memory
void freeSet(DisjointSet* ds) {
    free(ds->P);
    free(ds->R);
    free(ds);
}

int main() {
    int n;
    
    printf("Enter the total number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Number of elements must be greater than 0.\n");
        return 1;
    }

    DisjointSet* ds = createSet(n);
    int choice, x, y;

    while (1) {
        printf("\n--- Disjoint Set Operations ---\n");
        printf("1. Union two elements (x, y)\n");
        printf("2. Find the representative of an element (x)\n");
        printf("3. Exit\n");
        printf("Enter your choice (1/2/3): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter two elements to union (separated by space): ");
                scanf("%d %d", &x, &y);
                if (x >= 0 && x < n && y >= 0 && y < n) {
                    unionSets(ds, x, y);
                } else {
                    printf("Error: Elements must be between 0 and %d.\n", n - 1);
                }
                break;
                
            case 2:
                printf("Enter element to find: ");
                scanf("%d", &x);
                if (x >= 0 && x < n) {
                    printf("The representative (root) of %d is: %d\n", x, find(ds, x));
                } else {
                    printf("Error: Element must be between 0 and %d.\n", n - 1);
                }
                break;
                
            case 3:
                printf("Exiting and cleaning up memory...\n");
                freeSet(ds);
                return 0;
                
            default:
                printf("Invalid choice. Please select 1, 2, or 3.\n");
        }
    }

    freeSet(ds);
    return 0;
}