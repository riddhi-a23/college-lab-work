#include <stdio.h>
#include <stdlib.h>

int *P;
int *R;
int components; 

void initCity(int N) {
    P = (int*)malloc(N * sizeof(int));
    R = (int*)malloc(N * sizeof(int));
    components = N;
    
    for (int i = 0; i < N; i++) {
        P[i] = i;
        R[i] = 0;
    }
}

int findBuilding(int x) {
    if (P[x] != x) {
        P[x] = findBuilding(P[x]);
    }
    return P[x];
}

void buildRoad(int u, int v) {
    int rootU = findBuilding(u);
    int rootV = findBuilding(v);

    if (rootU != rootV) {
        if (R[rootU] > R[rootV]) {
            P[rootV] = rootU;
        } else if (R[rootU] < R[rootV]) {
            P[rootU] = rootV;
        } else {
            P[rootV] = rootU;
            R[rootU]++;
        }
        components--;
        printf("Road built between %d and %d.\n", u, v);
    } else {
        printf("Buildings %d and %d are already connected.\n", u, v);
    }
}

int main() {
    int N, M;
    printf("Enter number of buildings (N): ");
    scanf("%d", &N);
    
    initCity(N);
    
    printf("Enter number of road constructions (M): ");
    scanf("%d", &M);
    
    printf("\nEnter the %d road connections (u v):\n", M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        buildRoad(u, v);
        
        if (components == 1) {
            printf("The entire city is now FULLY connected!\n");
        } else {
            printf("City has %d separate components remaining.\n", components);
        }
    }

    free(P);
    free(R);
    return 0;
}