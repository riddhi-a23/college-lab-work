#include <iostream>
using namespace std;

namespace Sorting
{
    template <typename T>
    inline void swapElements(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    // Bubble sort
    template <typename T>
    void genericSort(T arr[], const int n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swapElements(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

struct Student {
    int rollNo;
    double marks;
};

int main()
{
    int n;
    cout << "Enter the number of elements (N): ";
    cin >> n;

    int* intArr = new int[n];
    cout << "\nEnter " << n << " integers: ";
    for (int i = 0; i < n; i++) cin >> intArr[i];

    Sorting::genericSort(intArr, n);
    
    cout << "Sorted integers: ";
    for (int i = 0; i < n; i++) cout << intArr[i] << " ";
    cout << endl;

    double* doubleArr = new double[n];
    cout << "\nEnter " << n << " doubles: ";
    for (int i = 0; i < n; i++) cin >> doubleArr[i];

    Sorting::genericSort(doubleArr, n);

    cout << "Sorted doubles: ";
    for (int i = 0; i < n; i++) cout << doubleArr[i] << " ";
    cout << endl;

    cout << "\n--- Testing with Struct Data Type ---" << endl;
    Student classroom[2] = {{102, 85.5}, {101, 92.0}};
    
    // Sorting::genericSort(classroom, 2); 

    delete[] intArr;
    delete[] doubleArr;
    intArr = nullptr;
    doubleArr = nullptr;

    return 0;
}