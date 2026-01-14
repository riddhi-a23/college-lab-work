#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

int exchanges = 0;

// Helper function to swap
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    exchanges++;
}

// Helper function to print array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// a) Insertion sort – i. Default algorithm
void insertionSort(int arr[], int n)
{
    exchanges = 0;
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
        {
            swap(&arr[j], &arr[j - 1]);
        }
    }
}

// a) Insertion sort – ii. Avoiding swap
void insertionSortShift(int arr[], int n)
{
    exchanges = 0;
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            exchanges++;
            j--;
        }
        arr[j + 1] = key;
    }
}

// b) Bubble sort – i. Default algorithm
void bubbleSort(int arr[], int n)
{
    exchanges = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

// b) Bubble sort – ii. Avoiding swap
void bubbleSortShift(int arr[], int n)
{
    exchanges = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int key = arr[j + 1];
                int k = j + 1;
                while (k > 0 && arr[k - 1] > key)
                {
                    arr[k] = arr[k - 1]; // shift right
                    exchanges++; // count this shift
                    k--;
                }
                arr[k] = key;
            }
        }
    }
}

// b) Bubble sort – iii. Flagged bubble sort
void flaggedBubbleSort(int arr[], int n)
{
    exchanges = 0;
    int swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

// b) Bubble sort – iv. Range limiting bubble sort
void rangeBubbleSort(int arr[], int n)
{
    exchanges = 0;
    int newn;
    while (n > 0)
    {
        newn = 0;
        for (int i = 1; i < n; i++)
        {
            if (arr[i - 1] > arr[i])
            {
                swap(&arr[i - 1], &arr[i]);
                newn = i;
            }
        }
        n = newn;
    }
}

// b) Bubble sort – v. Alternating bubble sort
void alternatingBubbleSort(int arr[], int n)
{
    exchanges = 0;
    int start = 0, end = n - 1, swapped = 1;
    while (swapped)
    {
        swapped = 0;
        for (int i = start; i < end; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
        swapped = 0;
        end--;
        for (int i = end - 1; i >= start; i--)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
        start++;
    }
}

// c) Merge sort – Default algorithm
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
            exchanges++;
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

// d) quick sort – default algorithm. here use “median of three” pivot selection algorithm.
int medianofthree(int arr[], int low, int high)
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
    int pivot = medianofthree(arr, low, high);
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

void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main()
{
    int list1[SIZE] = {1, 16, 12, 26, 25, 35, 33, 58, 45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95};
    int list2[SIZE] = {1, 17, 21, 42, 24, 27, 32, 35, 45, 47, 57, 23, 66, 69, 70, 76, 87, 85, 95, 99};
    int list3[SIZE] = {22, 20, 81, 38, 95, 84, 99, 12, 79, 44, 26, 87, 96, 10, 48, 80, 1, 31, 16, 92};

    int arr[SIZE];

    int num = 0;
    printf("Enter the list(1,2 or 3) you would want to sort: ");
    scanf("%d", &num);

    if (num == 1)
    {
        for (int i = 0; i < SIZE; i++)
            arr[i] = list1[i];
    }
    else if (num == 2)
    {
        for (int i = 0; i < SIZE; i++)
            arr[i] = list2[i];
    }
    else if (num == 3)
    {
        for (int i = 0; i < SIZE; i++)
            arr[i] = list3[i];
    }
    else
    {
        printf("List %d does not exist!!!!", num);
        return 0;
    }

    printf("Enter the sorting technique you would want to use: \n"
           "1. Insertion sort using default algorithm.\n"
           "2. Insertion sort avoiding swap.\n"
           "3. Bubble sort using default algorithm.\n"
           "4. Bubble sort avoiding swap.\n"
           "5. Flagged bubble sort.\n"
           "6. Range limiting bubble sort.\n"
           "7. Alternating bubble sort.\n"
           "8. Merge sort using default algorithm.\n"
           "9. Quick sort using default algorithm(median of three pivot selection algorithm).\n");
    int ch = -1;
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        printf("List %d sorted: ", num);
        insertionSort(arr, SIZE);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", arr[i]);
        printf("\nList %d Insertion Sort Exchanges: %d\n", num, exchanges);
        break;
    case 2:
        printf("List %d sorted: ", num);
        insertionSortShift(arr, SIZE);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", arr[i]);
        printf("\nList %d Insertion Sort (Shift) Exchanges: %d\n\n", num, exchanges);
        break;
    case 3:
        printf("List %d sorted: ", num);
        bubbleSort(arr, SIZE);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", arr[i]);
        printf("\nList %d Bubble Sort Exchanges: %d\n", num, exchanges);
        break;
    case 4:
        printf("List %d sorted: ", num);
        bubbleSortShift(arr, SIZE);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", arr[i]);
        printf("\nList %d Bubble Sort (Shift) Exchanges: %d\n", num, exchanges);
        break;
    case 5:
        printf("List %d sorted: ", num);
        flaggedBubbleSort(arr, SIZE);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", arr[i]);
        printf("\nList %d Flagged Bubble Sort Exchanges: %d\n", num, exchanges);
        break;
    case 6:
        printf("List %d sorted: ", num);
        rangeBubbleSort(arr, SIZE);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", arr[i]);
        printf("\nList %d Range Limiting Bubble Sort Exchanges: %d\n", num, exchanges);
        break;
    case 7:
        printf("List %d sorted: ", num);
        alternatingBubbleSort(arr, SIZE);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", arr[i]);
        printf("\nList %d Alternating Bubble Sort Exchanges: %d\n\n", num, exchanges);
        break;
    case 8:
        printf("List %d sorted: ", num);
        exchanges = 0;
        mergeSort(arr, 0, SIZE - 1);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", arr[i]);
        printf("\nList %d Merge Sort Exchanges: %d\n\n", num, exchanges);
        break;
    case 9:
        printf("List %d sorted: ", num);
        exchanges = 0;
        quickSort(arr, 0, SIZE - 1);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", arr[i]);
        printf("\nList %d Quick Sort (Median of Three) Exchanges: %d\n", num, exchanges);
        break;
    default:
        printf("Wrong choice!!!!");
        break;
    }

    return 0;
}
