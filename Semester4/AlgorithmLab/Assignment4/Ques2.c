#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATASET_SIZE 120000

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int partition(int arr[], int l, int r, int x) {
    int i;
    for (i = l; i < r; i++)
        if (arr[i] == x)
            break;
    swap(&arr[i], &arr[r]);

    i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

int medianOfMedians(int arr[], int l, int r, int k) {
    if (k > 0 && k <= r - l + 1) {
        int n = r - l + 1;

        int i, median[(n + 4) / 5]; 
        
        for (i = 0; i < n / 5; i++) {
            insertionSort(arr + l + i * 5, 5);
            median[i] = arr[l + i * 5 + 2];
        }

        if (i * 5 < n) {
            insertionSort(arr + l + i * 5, n % 5);
            median[i] = arr[l + i * 5 + (n % 5) / 2];
            i++;
        }

        int medOfMed = (i == 1) ? median[i - 1] :
                                  medianOfMedians(median, 0, i - 1, i / 2);

        int pos = partition(arr, l, r, medOfMed);

        if (pos - l == k - 1)
            return arr[pos];
        if (pos - l > k - 1) 
            return medianOfMedians(arr, l, pos - 1, k);

        return medianOfMedians(arr, pos + 1, r, k - pos + l - 1);
    }

    return -1;
}

int main() {
    int *household_incomes = (int *)malloc(DATASET_SIZE * sizeof(int));
    if (household_incomes == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    srand(time(0));

    for (int i = 0; i < DATASET_SIZE; i++) {
        household_incomes[i] = 10000 + rand() % 190001; 
    }

    int median = medianOfMedians(household_incomes, 0, DATASET_SIZE - 1, (DATASET_SIZE + 1) / 2);

    printf("Median Household Income: $%d\n", median);

    free(household_incomes);
    return 0;
}