#include <iostream>

using namespace std;

const int MAX_BOUND = 100; // Upper bound for inflation [cite: 25]

template <typename T>
struct GrowingStack {
    T* data;
    int top;
    int capacity;
};

// Initialize the stack [cite: 29]
template <typename T>
void initialize(GrowingStack<T> &s, int initialSize = 2) { // Default parameter [cite: 12]
    s.data = new T[initialSize];
    s.top = -1;
    s.capacity = initialSize;
}

// Inflate functionality [cite: 39]
template <typename T>
void inflate(GrowingStack<T> &s) {
    if (s.capacity >= MAX_BOUND) {
        cout << "Max bound reached. Cannot inflate." << endl;
        return;
    }
    int newCap = s.capacity * 2;
    T* newData = new T[newCap];
    for (int i = 0; i <= s.top; i++) newData[i] = s.data[i];
    delete[] s.data; // Free old memory [cite: 15]
    s.data = newData;
    s.capacity = newCap;
}

template <typename T>
void push(GrowingStack<T> &s, T val) {
    if (s.top + 1 == s.capacity) inflate(s);
    s.data[++s.top] = val;
}

int main() {
    GrowingStack<float> floatStack;
    initialize(floatStack);
    push(floatStack, 10.5f);
    push(floatStack, 20.7f);
    cout << "Current Stack Size: " << (floatStack.top + 1) << endl;
    return 0;
}