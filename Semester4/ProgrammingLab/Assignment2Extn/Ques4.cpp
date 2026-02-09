#include <iostream>
#include <string>

using namespace std;

// Generic swap using templates and reference variables [cite: 9, 11]
template <typename T>
inline void swapElements(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// Generic sort function [cite: 53]
template <typename T>
void genericSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // Note: This operator fails for basic structs [cite: 54]
                swapElements(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int n = 5;
    double dArr[] = {4.4, 1.1, 5.5, 2.2, 3.3};
    
    cout << "Sorting Double Array: ";
    genericSort(dArr, n);
    for(int i=0; i<n; i++) cout << dArr[i] << " ";
    cout << endl;

    return 0;
}