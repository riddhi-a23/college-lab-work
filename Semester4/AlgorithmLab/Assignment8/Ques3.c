#include <stdio.h>
#include <time.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsackRecursive(int W, int wt[], int val[], int n) {
    if (n == 0 || W == 0) {
        return 0;
    }

    if (wt[n - 1] > W) {
        return knapsackRecursive(W, wt, val, n - 1);
    }
    else {
        return max(
            val[n - 1] + knapsackRecursive(W - wt[n - 1], wt, val, n - 1),
            knapsackRecursive(W, wt, val, n - 1)
        );
    }   
}

int knapsackDP(int W, int wt[], int val[], int n) {
    int i, w;
    int K[n + 1][W + 1];

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }
    return K[n][W];
}

int main() {
    int val[] = {60, 100, 120, 90, 50}; 
    int wt[] = {10, 20, 30, 15, 5};     
    int W = 50;                         
    int n = sizeof(val) / sizeof(val[0]);

    clock_t start, end;
    double cpu_time_used;

    printf("Number of packages: %d\n", n);
    printf("Truck Capacity: %d\n\n", W);

    printf("--- Dynamic Programming Approach ---\n");
    start = clock();
    int dp_result = knapsackDP(W, wt, val, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Maximum Profit: %d\n", dp_result);
    printf("Execution Time: %f seconds\n\n", cpu_time_used);

    printf("--- Recursive Approach ---\n");
    start = clock();
    int rec_result = knapsackRecursive(W, wt, val, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Maximum Profit: %d\n", rec_result);
    printf("Execution Time: %f seconds\n", cpu_time_used);

    return 0;
}