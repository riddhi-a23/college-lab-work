#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
        {
            swap(&arr[j], &arr[j - 1]);
        }
    }
}

void merge(int arr[], int l, int m, int r)
{ // l is left index, m is middle index and r is right index;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // merging left and right halves
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
        {
            arr[k++] = R[j++];
        }
    }

    // copying remaining elements
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int medianOfThree(int arr[], int low, int high)
{
    int mid = (low + high) / 2;
    if (arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high])
        swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high])
        swap(&arr[mid], &arr[high]);
    swap(&arr[mid], &arr[high - 1]);
    return arr[high - 1];
}

int partition(int arr[], int low, int high)
{
    int pivot = medianOfThree(arr, low, high);
    int i = low, j = high - 1;
    while (1)
    {
        while (arr[++i] < pivot)
            ;
        while (arr[--j] > pivot)
            ;
        if (i >= j)
            break;
        swap(&arr[i], &arr[j]);
    }
    swap(&arr[i], &arr[high - 1]);
    return i;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void copyArray(int src[], int dest[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

int main()
{
    srand(time(NULL));
    int sizes[] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    int num_sizes = 10;

    printf("PERFORMANCE ANALYSIS OF SORTING ALGORITHMS\n");
    printf("=================================================================================\n");
    printf("| %-10s | %-12s | %-12s | %-12s | %-12s |\n", "Array Size", "Bubble (s)", "Insertion (s)", "Quick (s)", "Merge (s)");
    printf("=================================================================================\n");

    for (int i = 0; i < num_sizes; i++)
    {
        int n = sizes[i];

        int *masterArr = (int *)malloc(n * sizeof(int));
        int *workArr = (int *)malloc(n * sizeof(int));

        if (masterArr == NULL || workArr == NULL)
        {
            printf("Memory allocation failed!\n");
            return 1;
        }

        for (int i = 0; i < n; i++)
        {
            masterArr[i] = rand();
        }

        double t_bubble, t_insert, t_quick, t_merge;
        clock_t start, end;

        // 1. Measure Bubble Sort
        copyArray(masterArr, workArr, n);
        start = clock();
        bubbleSort(workArr, n);
        end = clock();
        t_bubble = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 2. Measure Insertion Sort
        copyArray(masterArr, workArr, n);
        start = clock();
        insertionSort(workArr, n);
        end = clock();
        t_insert = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 3. Measure Quick Sort
        copyArray(masterArr, workArr, n); 
        start = clock();
        quickSort(workArr, 0, n - 1);
        end = clock();
        t_quick = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 4. Measure Merge Sort
        copyArray(masterArr, workArr, n);
        start = clock();
        mergeSort(workArr, 0, n - 1);
        end = clock();
        t_merge = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("| %-10d | %-12.6f | %-12.6f | %-12.6f | %-12.6f |\n",
               n, t_bubble, t_insert, t_quick, t_merge);

        free(masterArr);
        free(workArr);
    }
    printf("=================================================================================\n");

    return 0;
}
