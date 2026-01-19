#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int thirdSmallest(int *arr, int n)
{
	int s1 = INT_MAX;
	int s2 = INT_MAX;
	int s3 = INT_MAX;

	for (int i = 0; i < n; i++)
	{
		if (arr[i] <= s1)
		{
			s3 = s2;
			s2 = s1;
			s1 = arr[i];
		}
		else if (arr[i] <= s2)
		{
			s3 = s2;
			s2 = arr[i];
		}
		else if (arr[i] < s3)
		{
			s3 = arr[i];
		}
	}
	return s3;
}

int fourthLargest(int *arr, int n)
{
	int l1 = INT_MIN;
	int l2 = INT_MIN;
	int l3 = INT_MIN;
	int l4 = INT_MIN;

	for (int i = 0; i < n; i++)
	{
		if (arr[i] >= l1)
		{
			l4 = l3;
			l3 = l2;
			l2 = l1;
			l1 = arr[i];
		}
		else if (arr[i] >= l2)
		{
			l4 = l3;
			l3 = l2;
			l2 = arr[i];
		}
		else if (arr[i] >= l3)
		{
			l4 = l3;
			l3 = arr[i];
		}
		else if (arr[i] > l4)
		{
			l4 = arr[i];
		}
	}
	return l4;
}

int main()
{
	srand(time(NULL));
	int n;
	do
	{
		printf("Enter the size(>=10) of the array: ");
		scanf("%d", &n);
		if (n < 10)
			printf("Size must be at least 10. Try again.\n");
	} while (n < 10);
	int *arr = (int *)malloc(sizeof(int) * n);
	if (arr == NULL)
	{
		printf("Memory allocation failed.\n");
		return 1;
	}
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand();
	}
	printf("The generated array with %d elements is:\n", n);
	for (int i = 0; i < n; i++)
	{
		printf("%d\t", arr[i]);
	}

	printf("\nThe 4th largest number in the array is %d.\n", fourthLargest(arr, n));
	printf("The 3rd smallest number in the array is %d.\n", thirdSmallest(arr, n));

	free(arr);

	return 0;
}
