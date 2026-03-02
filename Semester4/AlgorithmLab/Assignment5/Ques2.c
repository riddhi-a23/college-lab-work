#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *P;
int *R;

void initStudents(int n) {
    P = (int*)malloc(n * sizeof(int));
    R = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        P[i] = i; 
        R[i] = 0; 
    }
}

int findStudent(int x) {
    if (P[x] != x) {
        P[x] = findStudent(P[x]); 
    }
    return P[x];
}

void unionStudents(int x, int y) {
    int rootX = findStudent(x);
    int rootY = findStudent(y);

    if (rootX != rootY) {
        if (R[rootX] > R[rootY]) {
            P[rootY] = rootX;
        } else if (R[rootX] < R[rootY]) {
            P[rootX] = rootY;
        } else {
            P[rootY] = rootX;
            R[rootX]++;
        }
        printf("Students %d and %d became friends!\n", x, y);
    } else {
        printf("Students %d and %d are already in the same friend group.\n", x, y);
    }
}

int main() {
    int n, m;
    printf("Enter number of students (n): ");
    scanf("%d", &n);
    printf("Enter number of random friendship operations (m): ");
    scanf("%d", &m);

    initStudents(n);
    srand(time(NULL));

    printf("\n--- Processing %d Random Friendships ---\n", m);
    for (int i = 0; i < m; i++) {
        int u = rand() % n;
        int v = rand() % n;
        unionStudents(u, v);
    }

    free(P);
    free(R);
    return 0;
}