#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STUDENT_COUNT 110000

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partitionFixed(int *a, int low, int high)
{
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            swap(&a[++i], &a[j]);
        }
    }
    swap(&a[++i], &a[high]);
    return i;
}

int partitionRandom(int *a, int low, int high)
{
    int r = low + rand() % (high - low + 1);
    swap(&a[r], &a[high]);
    return partitionFixed(a, low, high);
}

int select(int *a, int low, int high, int k, int useRandom)
{
    if (low <= high)
    {
        int pi = useRandom ? partitionRandom(a, low, high) : partitionFixed(a, low, high);

        if (pi == k)
            return a[pi];
        if (pi > k)
            return select(a, low, pi - 1, k, useRandom);
        return select(a, pi + 1, high, k, useRandom);
    }
    return -1;
}

int main()
{
    int n = STUDENT_COUNT;
    int *a = malloc(n * sizeof(int));
    int *b = malloc(n * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 101;
        b[i] = a[i];
    }

    clock_t start = clock();
    int median1 = select(a, 0, n - 1, n / 2, 0); //0 for fixed partition and 1 for random partition
    clock_t end = clock();
    printf("Fixed Pivot Median: %d | Time: %f s\n", median1, (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    int median2 = select(b, 0, n - 1, n / 2, 1);
    end = clock();
    printf("Randomized Quickselect Median: %d | Time: %f s\n", median2, (double)(end - start) / CLOCKS_PER_SEC);

    free(a);
    free(b);
    return 0;
}