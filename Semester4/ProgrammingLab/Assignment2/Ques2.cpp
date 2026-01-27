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
        std::cout << "[Notice] Stack inflated to size " << s.capacity << "\n";
        return true;
    }

    void push(GrowingStack& s, int val) {
        if (isFull(s)) {
            if (!inflate(s)) {
                cout << "Error: Stack Overflow (Max limit reached)\n";
                return;
            }
        }
        s.elements[++s.top] = val;
    }

    int pop(GrowingStack& s) {
        if (isEmpty(s)) {
            cout << "Error: Stack Underflow\n";
            return -1; 
        }
        return s.elements[s.top--];
    }

    bool pop(GrowingStack& s, int& out_val) {
        if (isEmpty(s)) return false;
        out_val = s.elements[s.top--];
        return true;
    }

    void cleanup(GrowingStack& s) {
        delete[] s.elements;
        s.elements = nullptr;
    }
}

int main() {
    StackSystem::GrowingStack stack1, stack2, stack3;
    
    StackSystem::initialize(stack1, 10); 
    StackSystem::initialize(stack2, 10);
    StackSystem::initialize(stack3, 20); 

    for (int i = 1; i <= 5; i++) StackSystem::push(stack1, i * 10);
    for (int i = 1; i <= 3; i++) StackSystem::push(stack2, i * 100);   

    cout << "--- Processing Logic ---\n";
    
    int count = 1;
    while (!StackSystem::isEmpty(stack1) && !StackSystem::isEmpty(stack2)) {
        int val;
        // Odd count -> stack1, Even count -> stack2
        if (count % 2 != 0) {
            StackSystem::pop(stack1, val);
            cout << "Step " << count << " (Odd): Popped " << val << " from Stack1\n";
            StackSystem::push(stack3, val);
        } else {
            StackSystem::pop(stack2, val);
            cout << "Step " << count << " (Even): Popped " << val << " from Stack2\n";
            StackSystem::push(stack3, val);
        }
        count++;
    }

    while (!StackSystem::isEmpty(stack1)) {
        int val = StackSystem::pop(stack1);
        cout << "Stack2 empty. Draining Stack1: " << val << "\n";
        StackSystem::push(stack3, val);
    }
    while (!StackSystem::isEmpty(stack2)) {
        int val = StackSystem::pop(stack2);
        cout << "Stack1 empty. Draining Stack2: " << val << "\n";
        StackSystem::push(stack3, val);
    }

    cout << "\nFinal Stack3 Contents (Size: " << StackSystem::currentSize(stack3) << "):\n";
    while (!StackSystem::isEmpty(stack3)) {
        cout << StackSystem::pop(stack3) << " ";
    }
    cout << "\n";

    StackSystem::cleanup(stack1);
    StackSystem::cleanup(stack2);
    StackSystem::cleanup(stack3);

    return 0;
}