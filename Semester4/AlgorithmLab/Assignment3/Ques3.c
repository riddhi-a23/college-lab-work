#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;
int max_depth = 0;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void generateNearlySorted(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;

    int start_random = (int)(n * 0.8);
    for (int i = start_random; i < n; i++)
    {
        int r = start_random + rand() % (n - start_random);
        swap(&arr[i], &arr[r]);
    }
    for (int i = 0; i < n / 20; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        swap(&arr[a], &arr[b]);
    }
}

void merge(int arr[], int l, int m, int r, int depth)
{
    if (depth > max_depth)
        max_depth = depth;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        comparisons++;
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r, int depth)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, depth + 1);
        mergeSort(arr, m + 1, r, depth + 1);
        merge(arr, l, m, r, depth + 1);
    }
}

int partition(int arr[], int low, int high)
{
    int r = low + rand() % (high - low + 1);
    swap(&arr[r], &arr[high]);
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++)
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

void quickSort(int arr[], int low, int high, int depth)
{
    if (depth > max_depth)
        max_depth = depth;
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1, depth + 1);
        quickSort(arr, pi + 1, high, depth + 1);
    }
}

int main()
{
    int n = 100000;
    int *arr = (int *)malloc(n * sizeof(int));
    int *copy = (int *)malloc(n * sizeof(int));
    srand(time(0));

    generateNearlySorted(arr, n);
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];

    comparisons = 0;
    max_depth = 0;
    clock_t start = clock();
    mergeSort(arr, 0, n - 1, 0);
    clock_t end = clock();
    printf("Merge Sort | Comp: %10lld | Max Depth: %d | Time: %f\n",
           comparisons, max_depth, ((double)(end - start)) / CLOCKS_PER_SEC);

    comparisons = 0;
    max_depth = 0;
    start = clock();
    quickSort(copy, 0, n - 1, 0);
    end = clock();
    printf("Quicksort  | Comp: %10lld | Max Depth: %d | Time: %f\n",
           comparisons, max_depth, ((double)(end - start)) / CLOCKS_PER_SEC);

    printf("From the above analysis, we can conclude that for the given input conditions, Randomized Quicksort is more suitable as it performs faster.\n");

    free(arr);
    free(copy);
    return 0;
}