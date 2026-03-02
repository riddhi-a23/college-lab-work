#include <iostream>

using namespace std;

namespace StackSystem
{
    class GrowingStack
    {
    private:
        int *elements;
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
            this->elements = new int[this->capacity];
        }

        ~GrowingStack()
        {
            if (elements != nullptr) {
                delete[] elements;
                elements = nullptr;
            }
        }

        GrowingStack(const GrowingStack &other)
        {
            this->max_capacity = other.max_capacity;
            this->capacity = other.capacity;
            this->top = other.top;
            
            this->elements = new int[this->capacity];
            for (int i = 0; i <= this->top; i++) {
                this->elements[i] = other.elements[i];
            }
            cout << "Copy Constructor called.\n";
        }

        GrowingStack& operator=(const GrowingStack &other)
        {
            if (this != &other) 
            {
                delete[] elements; 

                this->max_capacity = other.max_capacity;
                this->capacity = other.capacity;
                this->top = other.top;

                // Deep Copy
                this->elements = new int[this->capacity];
                for (int i = 0; i <= this->top; i++) {
                    this->elements[i] = other.elements[i];
                }
            }
            cout << "Assignment Operator called.\n";
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

            int *new_elements = new int[new_capacity];

            for (int i = 0; i <= top; ++i) {
                new_elements[i] = elements[i];
            }

            delete[] elements;
            elements = new_elements;
            capacity = new_capacity;

            cout << "!!! Stack inflated. New Capacity: " << capacity << "\n";
            return true;
        }

        void push(int val)
        {
            if (isFull()) {
                if (!inflate()) {
                    cout << "Error: Stack Overflow (Max limit of " << max_capacity << " reached)\n";
                    return;
                }
            }
            elements[++top] = val;
        }

        void push(int inputs[], int count)
        {
            for (int i = 0; i < count; i++) {
                push(inputs[i]);
            }
            cout << "Pushed " << count << " elements.\n";
        }

        int pop()
        {
            if (isEmpty()) {
                cout << "Error: Stack Underflow\n";
                return -1;
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

int main()
{
    StackSystem::GrowingStack *stack1 = nullptr;
    StackSystem::GrowingStack *stack2 = nullptr;
    StackSystem::GrowingStack *stack3 = nullptr;

    int maxLim, initSize, count;

    cout << "Enter Max Capacity for Stack 1: ";
    cin >> maxLim;
    cout << "Enter Initial Size for Stack 1: ";
    cin >> initSize;

    stack1 = new StackSystem::GrowingStack(maxLim, initSize);

    cout << "How many numbers to push to Stack 1? ";
    cin >> count;
    if (count > 0)
    {
        int *inputArr = new int[count];
        cout << "Enter " << count << " numbers: ";
        for (int i = 0; i < count; i++)
            cin >> inputArr[i];

        stack1->push(inputArr, count); 
        delete[] inputArr;
    }

    cout << "\nEnter Max Capacity for Stack 2: ";
    cin >> maxLim;
    cout << "Enter Initial Size for Stack 2: ";
    cin >> initSize;
    
    stack2 = new StackSystem::GrowingStack(maxLim, initSize);

    cout << "How many numbers to push to Stack 2? ";
    cin >> count;
    if (count > 0)
    {
        int *inputArr = new int[count];
        cout << "Enter " << count << " numbers: ";
        for (int i = 0; i < count; i++)
            cin >> inputArr[i];

        stack2->push(inputArr, count);
        delete[] inputArr;
    }

    int totalMax = stack1->getMaxSize() + stack2->getMaxSize();
    stack3 = new StackSystem::GrowingStack(totalMax, 2);

    cout << "\n--- Creating stack3 ---\n";

    int step = 1;
    while (!stack1->isEmpty() && !stack2->isEmpty())
    {
        int val;
        if (step % 2 != 0)
        {
            val = stack1->pop();
            cout << "Step " << step << " (Odd): Pop " << val << " from Stack1\n";
            stack3->push(val);
        }
        else
        {
            val = stack2->pop();
            cout << "Step " << step << " (Even): Pop " << val << " from Stack2\n";
            stack3->push(val);
        }
        step++;
    }

    while (!stack1->isEmpty())
    {
        int val = stack1->pop();
        cout << "Stack2 empty. Popping from Stack1: " << val << "\n";
        stack3->push(val);
    }
    while (!stack2->isEmpty())
    {
        int val = stack2->pop();
        cout << "Stack1 empty. Popping from Stack2: " << val << "\n";
        stack3->push(val);
    }

    // DEMONSTRATING COPY CONSTRUCTOR
    // Creating stack4 as a copy of stack3
    cout << "\n--- Testing Copy Constructor (Creating Stack4 from Stack3) ---\n";
    StackSystem::GrowingStack stack4 = *stack3; 
    cout << "Stack4 created. Pop one element: " << stack4.pop() << endl;

    // DEMONSTRATING ASSIGNMENT OPERATOR
    cout << "\n--- Testing Assignment Operator (Assigning Stack4 to Stack5) ---\n";
    StackSystem::GrowingStack stack5(10, 2); 
    stack5 = stack4;
    cout << "Stack5 updated. Pop one element: " << stack5.pop() << endl;


    cout << "\nRemaining stack3 Elements: ";
    while (!stack3->isEmpty())
    {
        cout << stack3->pop() << " ";
    }
    cout << "\n";

    delete stack1;
    delete stack2;
    delete stack3;

    return 0;
}