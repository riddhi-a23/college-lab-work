#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int naive_comparisons = 0;
int dc_comparisons = 0;

struct MinMax
{
    int min;
    int max;
};

struct MinMax getMinMaxNaive(int arr[], int n)
{
    struct MinMax result;
    naive_comparisons = 0;

    if (n == 1)
    {
        result.max = arr[0];
        result.min = arr[0];
        return result;
    }

    if (arr[0] > arr[1])
    {
        result.max = arr[0];
        result.min = arr[1];
    }
    else
    {
        result.max = arr[1];
        result.min = arr[0];
    }
    naive_comparisons++;

    for (int i = 2; i < n; i++)
    {
        naive_comparisons++;
        if (arr[i] > result.max)
        {
            result.max = arr[i];
        }
        else
        {
            naive_comparisons++;
            if (arr[i] < result.min)
            {
                result.min = arr[i];
            }
        }
    }
    return result;
}

struct MinMax getMinMaxDC(int arr[], int low, int high)
{
    struct MinMax result, left, right;

    if (low == high)
    {
        result.max = arr[low];
        result.min = arr[low];
        return result;
    }

    if (high == low + 1)
    {
        dc_comparisons++;
        if (arr[low] > arr[high])
        {
            result.max = arr[low];
            result.min = arr[high];
        }
        else
        {
            result.max = arr[high];
            result.min = arr[low];
        }
        return result;
    }

    int mid = (low + high) / 2;
    left = getMinMaxDC(arr, low, mid);
    right = getMinMaxDC(arr, mid + 1, high);

    dc_comparisons++;
    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    dc_comparisons++;
    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    return result;
}

int main()
{
    srand(time(0));
    int sizes[] = {100, 1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);

    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        printf("Error: Could not create data.txt\n");
        return 1;
    }

    printf("%-10s | %-20s | %-20s\n", "Input Size", "Naive Comparisons", "D&C Comparisons");
    printf("------------------------------------------------------------\n");

    for (int t = 0; t < num_tests; t++)
    {
        int n = sizes[t];
        int *arr = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
            arr[i] = rand();

        getMinMaxNaive(arr, n);

        dc_comparisons = 0;
        getMinMaxDC(arr, 0, n - 1);

        printf("%-10d | %-20d | %-20d\n", n, naive_comparisons, dc_comparisons);
        fprintf(fp, "%d %d %d\n", n, naive_comparisons, dc_comparisons);

        free(arr);
    }

    fclose(fp);
    printf("\nSuccess! Data saved to 'data.txt'.\n");

    return 0;
}