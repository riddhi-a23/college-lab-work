#include <iostream>
using namespace std;

namespace StackSystem
{
    template <typename T>
    struct GrowingStack
    {
        T *elements;
        int top;
        int capacity;
        int max_capacity;
    };

    template <typename T>
    void initialize(GrowingStack<T> &s, int max_limit, int initial_size = 2)
    {
        s.capacity = initial_size;
        s.max_capacity = max_limit;
        s.top = -1;
        s.elements = new T[s.capacity];
    }

    template <typename T>
    inline bool isEmpty(const GrowingStack<T> &s)
    {
        return s.top == -1;
    }

    template <typename T>
    inline bool isFull(const GrowingStack<T> &s)
    {
        return s.top == s.capacity - 1;
    }

    template <typename T>
    inline int currentSize(const GrowingStack<T> &s)
    {
        return s.top + 1;
    }

    template <typename T>
    inline int getMaxSize(const GrowingStack<T> &s)
    {
        return s.max_capacity;
    }

    template <typename T>
    bool inflate(GrowingStack<T> &s)
    {
        if (s.capacity >= s.max_capacity)
        {
            return false;
        }

        int new_capacity = s.capacity * 2;
        if (new_capacity > s.max_capacity)
        {
            new_capacity = s.max_capacity;
        }

        T *new_elements = new T[new_capacity];
        for (int i = 0; i <= s.top; ++i)
        {
            new_elements[i] = s.elements[i];
        }

        delete[] s.elements;
        s.elements = new_elements;
        s.capacity = new_capacity;

        cout << "!!!Stack inflated. New Capacity: " << s.capacity << "\n";
        return true;
    }

    template <typename T>
    void push(GrowingStack<T> &s, T val)
    {
        if (isFull(s))
        {
            if (!inflate(s))
            {
                cout << "Error: Stack Overflow (Max limit of " << s.max_capacity << " reached)\n";
                return;
            }
        }
        s.top++;
        s.elements[s.top] = val;
    }

    template <typename T>
    void push(GrowingStack<T> &s, T inputs[], int count)
    {
        for (int i = 0; i < count; i++)
        {
            push(s, inputs[i]);
        }
        cout << "Pushed " << count << " elements.\n";
    }

    template <typename T>
    T pop(GrowingStack<T> &s)
    {
        if (isEmpty(s))
        {
            cout << "Error: Stack Underflow\n";
            return T();
        }
        return s.elements[s.top--];
    }

    template <typename T>
    void cleanup(GrowingStack<T> &s)
    {
        delete[] s.elements;
        s.elements = nullptr;
        s.top = -1;
        s.capacity = 0;
    }
}

struct Student
{
    string name;
    float gpa;
};

int main()
{
    // Integer Stack
    StackSystem::GrowingStack<int> intStack;
    int intMax, intInit, intCount;

    cout << "--- Integer Stack ---" << endl;
    cout << "Enter Max Capacity: "; cin >> intMax;
    cout << "Enter Initial Size: "; cin >> intInit;
    StackSystem::initialize(intStack, intMax, intInit); 

    cout << "How many integers to push? "; cin >> intCount;
    for (int i = 0; i < intCount; i++) {
        int val;
        cout << "Enter integer " << i + 1 << ": ";
        cin >> val;
        StackSystem::push(intStack, val);
    }

    cout << "Popping from Integer Stack: ";
    while (!StackSystem::isEmpty(intStack)) { 
        cout << StackSystem::pop(intStack) << " "; 
    }
    cout << endl;
    StackSystem::cleanup(intStack);

    // Float Stack
    StackSystem::GrowingStack<float> floatStack;
    int floatCount;

    cout << "\n--- Float Stack ---" << endl;
    StackSystem::initialize(floatStack, 10); 

    cout << "How many floats to push? "; cin >> floatCount;
    for (int i = 0; i < floatCount; i++) {
        float fVal;
        cout << "Enter float " << i + 1 << ": ";
        cin >> fVal;
        StackSystem::push(floatStack, fVal);
    }

    cout << "Current Float Stack Size: " << StackSystem::currentSize(floatStack) << endl;
    cout << "Popping Floats: ";
    while (!StackSystem::isEmpty(floatStack)) {
        cout << StackSystem::pop(floatStack) << " ";
    }
    cout << endl;
    StackSystem::cleanup(floatStack);

    // Struct Stack
    StackSystem::GrowingStack<Student> studentStack;
    int stuCount;

    cout << "\n--- Student Struct Stack Setup ---" << endl;
    StackSystem::initialize(studentStack, 5); 

    cout << "How many students to add? "; cin >> stuCount;
    for (int i = 0; i < stuCount; i++) {
        Student s;
        cout << "Enter Name for student " << i + 1 << ": ";
        cin >> s.name;
        cout << "Enter GPA: ";
        cin >> s.gpa;
        StackSystem::push(studentStack, s);
    }

    cout << "\nPopping Students:" << endl;
    while (!StackSystem::isEmpty(studentStack)) {
        Student s = StackSystem::pop(studentStack);
        cout << "Name: " << s.name << " | GPA: " << s.gpa << endl;
    }
    StackSystem::cleanup(studentStack);

    // String Stack
    StackSystem::GrowingStack<char*> stringStack;
    StackSystem::initialize(stringStack, 5);
    StackSystem::push(stringStack, (char*)"Hello!"); 
    cout << StackSystem::pop(stringStack); 
    StackSystem::cleanup(stringStack);

    return 0;
}