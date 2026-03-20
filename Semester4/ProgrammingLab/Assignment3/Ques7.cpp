#include <iostream>
#include <string>
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

        static const int POOL_SIZE = 100;
        static Student memoryPool[POOL_SIZE]; 
        static bool inUse[POOL_SIZE];       
        static bool poolInitialized;

        static void initPool()
        {
            if (!poolInitialized)
            {
                for (int i = 0; i < POOL_SIZE; i++)
                    inUse[i] = false;
                poolInitialized = true;
            }
        }

    public:
        Student() : name(""), age(0), department(""), year(0) {}

        void* operator new(size_t size)
        {
            initPool();
            for (int i = 0; i < POOL_SIZE; i++)
            {
                if (!inUse[i])
                {
                    inUse[i] = true;
                    cout << "[MemPool] Allocated slot " << i << endl;
                    return &memoryPool[i];
                }
            }
            throw bad_alloc(); 
        }

        void* operator new[](size_t size)
        {
            initPool();
            int count = size / sizeof(Student); 

            for (int i = 0; i <= POOL_SIZE - count; i++)
            {
                bool blockFree = true;
                for (int j = i; j < i + count; j++)
                {
                    if (inUse[j]) { blockFree = false; break; }
                }
                if (blockFree)
                {
                    for (int j = i; j < i + count; j++)
                        inUse[j] = true;
                    cout << "[MemPool] Allocated " << count
                         << " slots starting at " << i << endl;
                    return &memoryPool[i];
                }
            }
            throw bad_alloc(); 
        }

        void operator delete(void* ptr)
        {
            Student* s = static_cast<Student*>(ptr);
            int index = s - memoryPool;
            if (index >= 0 && index < POOL_SIZE)
            {
                inUse[index] = false;
                cout << "[MemPool] Released slot " << index << endl;
            }
        }

        void operator delete[](void* ptr)
        {
            Student* s = static_cast<Student*>(ptr);
            int index = s - memoryPool;
            if (index >= 0 && index < POOL_SIZE)
            {
                for (int i = index; i < POOL_SIZE && inUse[i]; i++)
                {
                    inUse[i] = false;
                    cout << "[MemPool] Released slot " << i << endl;
                }
            }
        }

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
            cout << "Year: " << this->year << endl
                 << endl;
        }
    };

    Student Student::memoryPool[Student::POOL_SIZE];
    bool    Student::inUse[Student::POOL_SIZE];
    bool    Student::poolInitialized = false;
}

int main()
{
    int N;
    cout << "Enter the number of students: ";
    cin >> N;

    StudentSystem::Student* students = new StudentSystem::Student[N];

    for (int i = 0; i < N; i++)
    {
        cout << "Enter details of Student " << (i + 1) << ": " << endl;
        students[i].ReadStudentData();
    }

    for (int i = 0; i < N; i++)
    {
        cout << "Details of Student " << (i + 1) << ": " << endl;
        students[i].PrintStudentData();
    }

    delete[] students;
    return 0;
}