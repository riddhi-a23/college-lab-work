#include <iostream>
#include <string>

using namespace std;

namespace StackSystem
{
    template <typename T>
    class GrowingStack
    {
    private:
        T *elements;
        int top;
        int capacity;
        int max_capacity;

        bool isFull() const {
            return top == capacity - 1;
        }

    public:
        GrowingStack(int max_limit, int initial_size)
        {
            this->max_capacity = max_limit;
            this->capacity = initial_size;
            this->top = -1;
            this->elements = new T[this->capacity];
        }

        ~GrowingStack()
        {
            if (elements != nullptr) {
                delete[] elements;
                elements = nullptr;
            }
        }

        GrowingStack(const GrowingStack<T> &other)
        {
            this->max_capacity = other.max_capacity;
            this->capacity = other.capacity;
            this->top = other.top;
            
            this->elements = new T[this->capacity];
            for (int i = 0; i <= this->top; i++) {
                this->elements[i] = other.elements[i];
            }
            cout << ">> Copy Constructor called.\n";
        }

        GrowingStack<T>& operator=(const GrowingStack<T> &other)
        {
            if (this != &other) 
            {
                delete[] elements; 

                this->max_capacity = other.max_capacity;
                this->capacity = other.capacity;
                this->top = other.top;

                this->elements = new T[this->capacity];
                for (int i = 0; i <= this->top; i++) {
                    this->elements[i] = other.elements[i];
                }
            }
            cout << ">> Assignment Operator called.\n";
            return *this;
        }

        bool inflate()
        {
            if (capacity >= max_capacity) {
                return false; 
            }

            int new_capacity = capacity * 2;
            if (new_capacity > max_capacity) {
                new_capacity = max_capacity;
            }

            T *new_elements = new T[new_capacity];

            for (int i = 0; i <= top; ++i) {
                new_elements[i] = elements[i];
            }

            delete[] elements;
            elements = new_elements;
            capacity = new_capacity;

            cout << "!!! Stack inflated. New Capacity: " << capacity << "\n";
            return true;
        }

        void push(T val)
        {
            if (isFull()) {
                if (!inflate()) {
                    cout << "Error: Stack Overflow (Max limit reached)\n";
                    return;
                }
            }
            elements[++top] = val;
        }

        void push(T inputs[], int count)
        {
            for (int i = 0; i < count; i++) {
                push(inputs[i]);
            }
            cout << "Pushed " << count << " elements.\n";
        }

        T pop()
        {
            if (isEmpty()) {
                cout << "Error: Stack Underflow\n";
                return T(); 
            }
            return elements[top--];
        }

        bool isEmpty() const {
            return top == -1;
        }

        int currentSize() const {
            return top + 1;
        }

        int getMaxSize() const {
            return max_capacity;
        }
    };
}

struct Student {
    string name;
    float gpa;
};

int main()
{
    // Integer Stack
    StackSystem::GrowingStack<int>* intStack = nullptr; 
    int intMax, intInit, intCount;

    cout << "--- Integer Stack ---" << endl;
    cout << "Enter Max Capacity: "; cin >> intMax;
    cout << "Enter Initial Size: "; cin >> intInit;
    
    intStack = new StackSystem::GrowingStack<int>(intMax, intInit); 

    cout << "How many integers to push? "; cin >> intCount;
    for (int i = 0; i < intCount; i++) {
        int val;
        cout << "Enter integer " << i + 1 << ": ";
        cin >> val;
        intStack->push(val);
    }

    cout << "Popping from Integer Stack: ";
    while (!intStack->isEmpty()) { 
        cout << intStack->pop() << " "; 
    }
    cout << endl;
    
    delete intStack; 

    // Float Stack
    StackSystem::GrowingStack<float>* floatStack = nullptr;
    int floatCount;

    cout << "\n--- Float Stack ---" << endl;
    floatStack = new StackSystem::GrowingStack<float>(10, 2); 

    cout << "How many floats to push? "; cin >> floatCount;
    for (int i = 0; i < floatCount; i++) {
        float fVal;
        cout << "Enter float " << i + 1 << ": ";
        cin >> fVal;
        floatStack->push(fVal);
    }

    cout << "Current Float Stack Size: " << floatStack->currentSize() << endl;
    cout << "Popping Floats: ";
    while (!floatStack->isEmpty()) {
        cout << floatStack->pop() << " ";
    }
    cout << endl;
    
    delete floatStack;


    // Struct Stack
    StackSystem::GrowingStack<Student>* studentStack = nullptr;
    int stuCount;

    cout << "\n--- Student Struct Stack Setup ---" << endl;
    studentStack = new StackSystem::GrowingStack<Student>(10, 2); // Max 10, Init 2

    cout << "How many students to add? "; cin >> stuCount;
    for (int i = 0; i < stuCount; i++) {
        Student s;
        cout << "Enter Name for student " << i + 1 << ": ";
        cin >> ws; // Clear whitespace
        getline(cin, s.name);
        cout << "Enter GPA: ";
        cin >> s.gpa;
        studentStack->push(s);
    }

    cout << "\nPopping Students:" << endl;
    while (!studentStack->isEmpty()) {
        Student s = studentStack->pop();
        cout << "Name: " << s.name << " | GPA: " << s.gpa << endl;
    }
    
    delete studentStack;


    // String Stack (char*)
    StackSystem::GrowingStack<const char*>* stringStack = nullptr;
    
    stringStack = new StackSystem::GrowingStack<const char*>(5, 2);
    
    stringStack->push("Hello!"); 
    cout << "\n--- String Stack ---" << endl;
    cout << "Popped: " << stringStack->pop() << endl; 
    
    delete stringStack;

    return 0;
}