#include <stdio.h>
#include <time.h>

unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

unsigned long long fibonacci_dp(int n) {
    if (n <= 1) {
        return n;
    }

    unsigned long long dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    clock_t start, end;
    double cpu_time_used;

    printf("\n--- Dynamic Programming Method ---\n");
    start = clock();
    unsigned long long result_dp = fibonacci_dp(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Fibonacci(%d) = %llu\n", n, result_dp);
    printf("Execution Time: %f seconds\n", cpu_time_used);

    printf("\n--- Recursive Method ---\n");
    start = clock();
    unsigned long long result_rec = fibonacci_recursive(n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Fibonacci(%d) = %llu\n", n, result_rec);
    printf("Execution Time: %f seconds\n", cpu_time_used);

    return 0;
}