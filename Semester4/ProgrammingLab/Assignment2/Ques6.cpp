#include <iostream>
#include <cstring>

using namespace std;

namespace StackSystem
{
    struct GrowingStack
    {
        void **elements;
        int top;
        int capacity;
        int max_capacity;
        int element_size;
    };

    void initialize(GrowingStack &s, int max_limit, int elem_size, int initial_size = 2)
    {
        s.capacity = initial_size;
        s.max_capacity = max_limit;
        s.element_size = elem_size;
        s.top = -1;
        s.elements = new void *[s.capacity];
    }

    inline bool isEmpty(const GrowingStack &s) { return s.top == -1; }
    inline bool isFull(const GrowingStack &s) { return s.top == s.capacity - 1; }
    inline int currentSize(const GrowingStack &s) { return s.top + 1; }
    inline int getMaxSize(const GrowingStack &s) { return s.max_capacity; }

    bool inflate(GrowingStack &s)
    {
        if (s.capacity >= s.max_capacity)
            return false;

        int new_capacity = (s.capacity * 2 > s.max_capacity) ? s.max_capacity : s.capacity * 2;
        void **new_elements = new void *[new_capacity];

        for (int i = 0; i <= s.top; ++i)
            new_elements[i] = s.elements[i];

        delete[] s.elements;
        s.elements = new_elements;
        s.capacity = new_capacity;

        cout << "!!!Stack inflated. New Capacity: " << s.capacity << "\n";
        return true;
    }

    void push(GrowingStack &s, void *valAddr)
    {
        if (isFull(s))
        {
            if (!inflate(s))
            {
                cout << "Error: Stack Overflow\n";
                return;
            }
        }
        s.top++;
        s.elements[s.top] = malloc(s.element_size);
        memcpy(s.elements[s.top], valAddr, s.element_size);
    }

    void pop(GrowingStack &s, void *destAddr)
    {
        if (isEmpty(s))
        {
            cout << "Error: Stack Underflow\n";
            return;
        }
        memcpy(destAddr, s.elements[s.top], s.element_size);
        free(s.elements[s.top]);
        s.top--;
    }

    void cleanup(GrowingStack &s)
    {
        for (int i = 0; i <= s.top; i++)
            free(s.elements[i]);
        delete[] s.elements;
        s.elements = nullptr;
        s.top = -1;
        s.capacity = 0;
    }
}

struct Student
{
    char name[20];
    float gpa;
};

int main()
{
    //Integer stack
    StackSystem::GrowingStack intStack;
    StackSystem::initialize(intStack, 20, sizeof(int)); 
    
    int numInts;
    cout << "--- Integer Stack ---" << endl;
    cout << "How many integers to push? ";
    cin >> numInts;

    for (int i = 0; i < numInts; i++) {
        int temp;
        cout << "Enter integer " << i + 1 << ": ";
        cin >> temp;
        StackSystem::push(intStack, &temp); 
    }

    cout << "Popping all integers: ";
    int iOut;
    while (!StackSystem::isEmpty(intStack)) {
        StackSystem::pop(intStack, &iOut);
        cout << iOut << " ";
    }
    cout << endl;
    StackSystem::cleanup(intStack); 

    // --- 2. Float Stack with Multiple Elements ---
    StackSystem::GrowingStack floatStack;
    StackSystem::initialize(floatStack, 10, sizeof(float)); 

    int fCount;
    cout << "--- Float Stack ---" << endl;
    cout << "How many floats to push? ";
    cin >> fCount;

    for (int i = 0; i < fCount; i++) {
        float fTemp;
        cout << "Enter float " << i + 1 << ": ";
        cin >> fTemp;
        StackSystem::push(floatStack, &fTemp); 
    }

    cout << "Popping floats: ";
    float fOut;
    while (!StackSystem::isEmpty(floatStack)) {
        StackSystem::pop(floatStack, &fOut);
        cout << fOut << " ";
    }
    cout << endl;
    StackSystem::cleanup(floatStack);

    // Struct Stack
    StackSystem::GrowingStack stuStack;
    StackSystem::initialize(stuStack, 5, sizeof(Student)); 

    int numStudents;
    cout << "\n--- Student Struct Stack ---" << endl;
    cout << "How many students to push? ";
    cin >> numStudents;

    for (int i = 0; i < numStudents; i++) {
        Student s;
        cout << "Enter Name for student " << i + 1 << ": ";
        cin >> s.name;
        cout << "Enter GPA: ";
        cin >> s.gpa;
        StackSystem::push(stuStack, &s);
    }

    Student sOut;
    while (!StackSystem::isEmpty(stuStack)) {
        StackSystem::pop(stuStack, &sOut);
        cout << "Popped Student: " << sOut.name << " (GPA: " << sOut.gpa << ")" << endl;
    }
    StackSystem::cleanup(stuStack); 

    //String Stack
    StackSystem::GrowingStack stringStack;
    StackSystem::initialize(stringStack, 5, sizeof(char*));

    int sCount;
    cout << "\n--- String Stack (Universal) ---" << endl;
    cout << "How many strings to push? ";
    cin >> sCount;

    // We need an array of buffers to keep strings alive if pushing multiple
    char buffers[10][100]; 

    for (int i = 0; i < sCount; i++) {
        cout << "Enter string " << i + 1 << ": ";
        cin >> buffers[i];
        char* strPtr = buffers[i];
        StackSystem::push(stringStack, &strPtr);  
    }

    cout << "Popping strings: ";
    char* strOut;
    while (!StackSystem::isEmpty(stringStack)) {
        StackSystem::pop(stringStack, &strOut);
        cout << "\"" << strOut << "\" ";
    }
    cout << endl;
    StackSystem::cleanup(stringStack);

    return 0;
}