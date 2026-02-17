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
            cout << "Year: " << this->year << endl
                 << endl;
        }
    };
}

int main()
{
    int N;
    cout << "Enter the number of students: ";
    cin >> N;
    StudentSystem::Student *students = new StudentSystem::Student[N];
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