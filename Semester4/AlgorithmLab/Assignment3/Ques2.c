#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;
int max_recursion_depth = 0;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void generateDuplicateArray(int arr[], int n, int percent_duplicates) {
    for(int i = 0; i < n; i++) arr[i] = rand() % n;
    
    int limit = (n * percent_duplicates) / 100;
    int duplicate_val = rand() % n; 
    for(int i = 0; i < limit; i++) {
        arr[i] = duplicate_val;
    }
    
    for (int i = 0; i < n; i++) {
        int r = rand() % n;
        swap(&arr[i], &arr[r]);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (arr[j] <= pivot) { 
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

int randomizedPartition(int arr[], int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}

void quickSort(int arr[], int low, int high, int isRandom, int depth) {
    if (depth > max_recursion_depth) max_recursion_depth = depth;

    if (low < high) {
        int pi;
        if (isRandom) pi = randomizedPartition(arr, low, high);
        else pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1, isRandom, depth + 1);
        quickSort(arr, pi + 1, high, isRandom, depth + 1);
    }
}

void runTest(int arr[], int n, int duplicate_pct, FILE *dataFile) {
    int *copy = (int*)malloc(n * sizeof(int));
    clock_t start, end;
    
    double std_time, rand_time;
    long long std_comp, rand_comp;
    int std_depth, rand_depth;

    for(int i=0; i<n; i++) copy[i] = arr[i]; 
    comparisons = 0;
    max_recursion_depth = 0;
    
    start = clock();
    quickSort(copy, 0, n - 1, 0, 0);
    end = clock();
    
    std_time = ((double)(end-start))/CLOCKS_PER_SEC;
    std_comp = comparisons;
    std_depth = max_recursion_depth;

    for(int i=0; i<n; i++) copy[i] = arr[i];
    comparisons = 0;
    max_recursion_depth = 0;
    
    start = clock();
    quickSort(copy, 0, n - 1, 1, 0);
    end = clock();

    rand_time = ((double)(end-start))/CLOCKS_PER_SEC;
    rand_comp = comparisons;
    rand_depth = max_recursion_depth;

    printf("Standard   | %3d%% Duplicates | Comp: %10lld | Depth: %5d | Time: %f\n", 
            duplicate_pct, std_comp, std_depth, std_time);
    printf("Randomized | %3d%% Duplicates | Comp: %10lld | Depth: %5d | Time: %f\n", 
            duplicate_pct, rand_comp, rand_depth, rand_time);
    printf("-----------------------------------------------------------------------\n");

    fprintf(dataFile, "%d %f %f %lld %lld %d %d\n", 
            duplicate_pct, std_time, rand_time, std_comp, rand_comp, std_depth, rand_depth);

    free(copy);
}

int main() {
    int n = 100000;
    int *arr = (int*)malloc(n * sizeof(int));
    srand(time(0));

    FILE *fp = fopen("data.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "# Duplicates Std_Time Rand_Time Std_Comp Rand_Comp Std_Depth Rand_Depth\n");
    
    printf("Running 10%% test...\n");
    generateDuplicateArray(arr, n, 10);
    runTest(arr, n, 10, fp);

    printf("Running 50%% test...\n");
    generateDuplicateArray(arr, n, 50);
    runTest(arr, n, 50, fp);

    printf("Running 90%% test...\n");
    generateDuplicateArray(arr, n, 90);
    runTest(arr, n, 90, fp);

    fclose(fp);
    free(arr);
    
    printf("\nData successfully written to 'data.txt'.\n");
    return 0;
}