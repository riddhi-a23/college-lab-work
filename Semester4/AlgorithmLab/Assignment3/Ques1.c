#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        comparisons++;
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

int randomizedPartition(int arr[], int low, int high)
{
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}

void randomizedQuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

void generateData(int arr[], int n, int type)
{
    for (int i = 0; i < n; i++)
    {
        if (type == 1)
            arr[i] = i;
        else if (type == 2)
            arr[i] = n - i;
        else
            arr[i] = rand() % n;
    }
}

int main()
{
    int n = 100000;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed");
        return 1;
    }

    srand(time(0));
    clock_t start, end;
    double cpu_time_used;

    printf("%-20s %-20s %-20s\n", "Scenario", "Comparisons", "Time");

    char *scenarios[] = {"Best", "Worst", "Average"};
    for (int t = 1; t <= 3; t++)
    {
        generateData(arr, n, t);

        comparisons = 0;
        start = clock();
        randomizedQuickSort(arr, 0, n - 1);
        end = clock();

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%-20s %-20lld %-20f\n", scenarios[t - 1], comparisons, cpu_time_used);
    }

    free(arr);
    return 0;
}