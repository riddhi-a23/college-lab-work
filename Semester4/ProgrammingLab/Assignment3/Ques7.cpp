#include <iostream>
#include <string>
#include <new> // Required for std::bad_alloc

using namespace std;

namespace StudentSystem
{
    class Student
    {
    private:
        string name;
        int age;
        string department;
        int year;

        // --- Memory Pool Variables ---
        static const int MAX_POOL_SIZE = 10; // Maximum objects the pool can hold
        static char memoryPool[MAX_POOL_SIZE * sizeof(StudentSystem::Student)]; // Raw memory pool
        static bool slotInUse[MAX_POOL_SIZE];

    public:
        Student() : name(""), age(0), department(""), year(0) {}

        void ReadStudentData()
        {
            cout << "Enter name: ";
            cin >> ws;
            getline(cin, name);
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter department: ";
            cin >> ws;
            getline(cin, department);
            cout << "Enter year: ";
            cin >> year;
        }

        void PrintStudentData() const
        {
            cout << "Name: " << this->name << endl;
            cout << "Age: " << this->age << endl;
            cout << "Department: " << this->department << endl;
            cout << "Year: " << this->year << endl << endl;
        }

        // --- Custom Memory Management ---
        
        // Custom 'new' operator fetching memory from the pool
        static void* operator new(size_t size)
        {
            for (int i = 0; i < MAX_POOL_SIZE; i++) {
                if (!slotInUse[i]) {
                    slotInUse[i] = true;
                    cout << "[Memory Pool] Allocated Student object at slot " << i << ".\n";
                    return memoryPool + (i * sizeof(Student));
                }
            }
            cout << "[Memory Pool] Error: Pool exhausted!\n";
            throw std::bad_alloc();
        }

        // Custom 'delete' operator returning memory to the pool
        static void operator delete(void* ptr)
        {
            if (!ptr) return;
            
            // Match the pointer back to its slot in the pool
            for (int i = 0; i < MAX_POOL_SIZE; i++) {
                if (memoryPool + (i * sizeof(Student)) == ptr) {
                    slotInUse[i] = false;
                    cout << "[Memory Pool] Returned Student object at slot " << i << " to the pool.\n";
                    return;
                }
            }
        }
    };

    // Initialize static member variables for the memory pool outside the class
    char Student::memoryPool[MAX_POOL_SIZE * sizeof(Student)];
    bool Student::slotInUse[MAX_POOL_SIZE] = {false};
}

int main()
{
    int N;
    cout << "Enter the number of students (Max 10): ";
    cin >> N;

    // Use an array of pointers to trigger the custom single-object 'new' operator
    StudentSystem::Student** students = new StudentSystem::Student*[N];

    for (int i = 0; i < N; i++)
    {
        cout << "\n--- Student " << (i + 1) << " ---" << endl;
        // This line calls our custom static void* operator new(size_t)
        students[i] = new StudentSystem::Student(); 
        students[i]->ReadStudentData();
    }

    cout << "\n--- Outputting Data ---\n";
    for (int i = 0; i < N; i++)
    {
        cout << "Details of Student " << (i + 1) << ":" << endl;
        students[i]->PrintStudentData();
    }

    cout << "--- Cleaning Up Memory ---\n";
    for (int i = 0; i < N; i++)
    {
        // This line calls our custom static void operator delete(void*)
        delete students[i]; 
    }
    
    // Clean up the dynamically allocated pointer array itself
    delete[] students; 

    return 0;
}