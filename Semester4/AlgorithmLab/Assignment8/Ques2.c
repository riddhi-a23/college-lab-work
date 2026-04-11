#include <stdio.h>
#include <limits.h>
#include <time.h>

int matrixChainRecursive(int p[], int i, int j) {
    if (i == j) {
        return 0;
    }
    
    int k;
    int min = INT_MAX;
    int count;

    for (k = i; k < j; k++) {
        count = matrixChainRecursive(p, i, k) +
                matrixChainRecursive(p, k + 1, j) +
                p[i - 1] * p[k] * p[j];

        if (count < min) {
            min = count;
        }
    }
    return min;
}

int matrixChainDP(int p[], int n) {
    int m[n][n];
    int i, j, k, L, q;

    for (i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    for (L = 2; L < n; L++) {
        for (i = 1; i < n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }
    
    return m[1][n - 1];
}

int main() {
    int arr[] = {10, 30, 5, 60}; 
    int n = sizeof(arr) / sizeof(arr[0]);

    clock_t start, end;
    double cpu_time_used;

    printf("Matrix Dimensions Array: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    printf("--- Dynamic Programming Approach ---\n");
    start = clock();
    int dp_result = matrixChainDP(arr, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Minimum number of scalar multiplications: %d\n", dp_result);
    printf("Execution Time: %f seconds\n\n", cpu_time_used);

    printf("--- Recursive Approach ---\n");
    start = clock();
    int rec_result = matrixChainRecursive(arr, 1, n - 1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Minimum number of scalar multiplications: %d\n", rec_result);
    printf("Execution Time: %f seconds\n", cpu_time_used);

    return 0;
}