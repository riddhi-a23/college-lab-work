#include<iostream>
#include "array_fxn.h"
using namespace std;

int largest(int arr[], int n)
{
    if (n == 1)
    {
        return arr[0];
    }
    int maxofRest = largest(arr, n - 1);
    if (arr[n - 1] > maxofRest)
    {
        return arr[n - 1];
    }
    else
    {
        return maxofRest;
    }
}

bool search(int arr[], int n, int num, int i)
{
    if (i == n)
    {
        return false;
    }
    if (arr[i] == num)
    {
        return true;
    }
    return search(arr, n, num, i + 1);
}

void printReverse(int arr[], int n)
{
    if (n == 0)
    {
        return;
    }
    cout << arr[n - 1] << " ";
    printReverse(arr, n - 1);
}

int sum(int arr[], int n)
{
    if (n == 0)
    {
        return 0;
    }
    return arr[n - 1] + sum(arr, n - 1);
}

