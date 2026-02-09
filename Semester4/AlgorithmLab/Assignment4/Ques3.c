#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

double findMedianSortedArrays(int *arr1, int n, int *arr2, int m)
{
    if (n > m)
    {
        return findMedianSortedArrays(arr2, m, arr1, n);
    }

    int l = 0;
    int r = n - 1;
    int total = n + m;
    int half = total / 2;

    while (1)
    {
        int i = (l + r) / 2;        // pointer for arr1
        int j = half - (i + 1) - 1; // pointer for arr2

        int left1 = (i >= 0) ? arr1[i] : INT_MIN;
        int right1 = ((i + 1) < n) ? arr1[i + 1] : INT_MAX;

        int left2 = (j >= 0) ? arr2[j] : INT_MIN;
        int right2 = ((j + 1) < m) ? arr2[j + 1] : INT_MAX;

        // partition is correct
        if (left1 <= right2 && left2 <= right1)
        {
            // odd
            if (total % 2 == 1)
            {
                return (double)MIN(right1, right2);
            }
            else
            {
                return (MAX(left1, left2) + MIN(right1, right2)) / 2.0;
            }
        }
        else if (left1 > right2)
        {
            // reduce size of arr1
            r = i - 1;
        }
        else
        {
            l = i + 1;
        }
    }
}

int main()
{
    int bankA_transactions[] = {1200, 1500, 2000, 2500, 3000};
    int n = sizeof(bankA_transactions) / sizeof(bankA_transactions[0]);

    int bankB_transactions[] = {1100, 1800, 2100, 2400, 2900, 3200};
    int m = sizeof(bankB_transactions) / sizeof(bankB_transactions[0]);

    printf("Bank A Data: ");
    for (int i = 0; i < n; i++)
        printf("%d ", bankA_transactions[i]);
    printf("\n");

    printf("Bank B Data: ");
    for (int i = 0; i < m; i++)
        printf("%d ", bankB_transactions[i]);
    printf("\n");

    double median = findMedianSortedArrays(bankA_transactions, n, bankB_transactions, m);

    printf("\nMedian Transaction Value: %.2f\n", median);

    return 0;
}