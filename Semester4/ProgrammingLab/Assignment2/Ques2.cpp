#include <iostream>
using namespace std;

namespace StackSystem {
    struct GrowingStack {
        int* elements;     
        int top;           
        int capacity;      
        int max_capacity;   
    };

    void initialize(GrowingStack& s, int max_limit, int initial_size = 2) {
        s.capacity = initial_size;
        s.max_capacity = max_limit;
        s.top = -1;
        s.elements = new int[s.capacity];
    }

    inline bool isEmpty(const GrowingStack& s) {
        return s.top == -1;
    }

    inline bool isFull(const GrowingStack& s) {
        return s.top == s.capacity - 1;
    }

    inline int currentSize(const GrowingStack& s) {
        return s.top + 1;
    }

    inline int getMaxSize(const GrowingStack& s) {
        return s.max_capacity;
    }
    
    bool inflate(GrowingStack& s) {
        if (s.capacity >= s.max_capacity) {
            return false;
        }

        int new_capacity = s.capacity * 2;
        if (new_capacity > s.max_capacity) {
            new_capacity = s.max_capacity;
        }

        int* new_elements = new int[new_capacity];
        
        for (int i = 0; i <= s.top; ++i) {
            new_elements[i] = s.elements[i];
        }

        delete[] s.elements;
        s.elements = new_elements;
        s.capacity = new_capacity;
        
        cout << "!!!Stack inflated. New Capacity: " << s.capacity << "\n";
        return true;
    }

    void push(GrowingStack& s, int val) {
        if (isFull(s)) {
            if (!inflate(s)) {
                cout << "Error: Stack Overflow (Max limit of " << s.max_capacity << " reached)\n";
                return;
            }
        }
        s.top++;
        s.elements[s.top] = val;
    }

    void push(GrowingStack& s, int inputs[], int count) {
        for(int i = 0; i < count; i++) {
            push(s, inputs[i]);
        }
        cout << "Pushed " << count << " elements.\n";
    }

    int pop(GrowingStack& s) {
        if (isEmpty(s)) {
            cout << "Error: Stack Underflow\n";
            return -1; 
        }
        return s.elements[s.top--];
    }

    void cleanup(GrowingStack& s) {
        delete[] s.elements;
        s.elements = nullptr;
        s.top = -1;
    }
}

int main() {
    StackSystem::GrowingStack stack1, stack2, stack3;
    int maxLim, initSize, count;

    cout << "Enter Max Capacity for Stack 1: "; cin >> maxLim;
    cout << "Enter Initial Size for Stack 1: "; cin >> initSize;
    StackSystem::initialize(stack1, maxLim, initSize);

    cout << "How many numbers to push to Stack 1? "; cin >> count;
    if (count > 0) {
        int* inputArr = new int[count]; 
        cout << "Enter " << count << " numbers: ";
        for (int i = 0; i < count; i++) cin >> inputArr[i];
        
        StackSystem::push(stack1, inputArr, count);
        delete[] inputArr; 
    }

    cout << "\nEnter Max Capacity for Stack 2: "; cin >> maxLim;
    cout << "Enter Initial Size for Stack 2: "; cin >> initSize;
    StackSystem::initialize(stack2, maxLim, initSize);

    cout << "How many numbers to push to Stack 2? "; cin >> count;
    if (count > 0) {
        int* inputArr = new int[count]; 
        cout << "Enter " << count << " numbers: ";
        for (int i = 0; i < count; i++) cin >> inputArr[i];

        StackSystem::push(stack2, inputArr, count);
        delete[] inputArr;
    }

    int totalMax = StackSystem::getMaxSize(stack1) + StackSystem::getMaxSize(stack2);
    StackSystem::initialize(stack3, totalMax, 2); 

    cout << "\n--- Creating stack3 ---\n";
    
    int step = 1;
    while (!StackSystem::isEmpty(stack1) && !StackSystem::isEmpty(stack2)) {
        int val;
        if (step % 2 != 0) {
            val = StackSystem::pop(stack1);
            cout << "Step " << step << " (Odd): Pop " << val << " from Stack1\n";
            StackSystem::push(stack3, val);
        } else {
            val = StackSystem::pop(stack2);
            cout << "Step " << step << " (Even): Pop " << val << " from Stack2\n";
            StackSystem::push(stack3, val);
        }
        step++;
    }

    while (!StackSystem::isEmpty(stack1)) {
        int val = StackSystem::pop(stack1);
        cout << "Stack2 empty. Popping from Stack1: " << val << "\n";
        StackSystem::push(stack3, val);
    }
    while (!StackSystem::isEmpty(stack2)) {
        int val = StackSystem::pop(stack2);
        cout << "Stack1 empty. Popping from Stack2: " << val << "\n";
        StackSystem::push(stack3, val);
    }

    cout << "\nstack3 Elements: ";
    while (!StackSystem::isEmpty(stack3)) {
        cout << StackSystem::pop(stack3) << " ";
    }
    cout << "\n";

    StackSystem::cleanup(stack1);
    StackSystem::cleanup(stack2);
    StackSystem::cleanup(stack3);

    return 0;
}