#include <iostream>
#include <cstring>

using namespace std;

struct UniversalStack {
    void** data; // Array of pointers to hold any type
    int top;
    int capacity;
    int elementSize;
};

void initialize(UniversalStack &s, int elemSize, int initialSize = 5) {
    s.data = new void*[initialSize];
    s.top = -1;
    s.capacity = initialSize;
    s.elementSize = elemSize;
}

void push(UniversalStack &s, void* valAddr) {
    if (s.top + 1 < s.capacity) {
        // Allocate space for the specific element type
        s.data[++s.top] = malloc(s.elementSize);
        memcpy(s.data[s.top], valAddr, s.elementSize);
    }
}

int main() {
    UniversalStack stringStack;
    initialize(stringStack, sizeof(char*));

    const char* msg = "Hello";
    push(stringStack, &msg);

    cout << "Universal Stack (string) initialized and populated." << endl;
    
    // Cleanup to prevent memory leaks [cite: 15]
    for(int i=0; i<=stringStack.top; i++) free(stringStack.data[i]);
    delete[] stringStack.data;
    
    return 0;
}