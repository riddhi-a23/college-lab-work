#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int partition(int arr[], int low, int high)
{
    int p = rand() % (high-low+1) + low;
    int pivot = arr[p];
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

int main(){
	srand(time(NULL));
	int arr[100000];
	for(int i=0;i<100000;i++){
	arr[i]=rand();
	}


	return 0;
}
