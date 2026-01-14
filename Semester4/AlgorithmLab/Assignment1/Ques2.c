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


int main()
{
    srand(time(NULL));
    int size = 50000;
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand();
    }
    int num;
    printf("Enter the element to be searched in the array: ");
    scanf("%d", &num);
    // Linear Search
    clock_t start, end;
    int comp1 = 0;
    int idx = -1;
    double t1;
    start = clock();
    for (int i = 0; i < size; i++)
    {
        comp1++;
        if (arr[i] == num)
        {
            idx = i;
            break;
        }
    }
    end = clock();
    t1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Linear Search:\n");
    if (idx != -1)
    {
        printf("Element found at index %d in the array.\n", idx);
    }
    else
    {
        printf("Element not found in the array.\n");
    }
    printf("Number of Comparisons performed: %d\n", comp1);
    printf("Time taken to locate the element: %f\n", t1);
    // Binary Search
    idx = -1;
    double t2;
    int comp2 = 0;
    bubbleSort(arr,size);
    int left = 0;
    int right = size - 1;
    start = clock();
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (num < arr[mid])
        {
            right = mid - 1;
        }
        else if (num > arr[mid])
        {
            left = mid + 1;
        }
        else
        {
            idx = mid;
            break;
        }
        comp2++;
    }
    end = clock();
    t2 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Binary Search:\n");
    if (idx != -1)
    {
        printf("Element found at index %d in the array.\n", idx);
    }
    else
    {
        printf("Element not found in the array.\n");
    }
    printf("Number of Comparisons performed: %d\n", comp2);
    printf("Time taken to locate the element: %f\n", t2);
    return 0;
}
