#include <iostream>
#include <string>
using namespace std;

namespace StudentSystem
{
	struct Student
	{
		string name;
		int age;
		string department;
		int year;
	};

	void ReadStudentData(Student &s)
	{
		cout << "Enter name: ";
		cin >> ws;
		getline(cin, s.name);
		cout << "Enter age: ";
		cin >> s.age;
		cout << "Enter department: ";
		cin >> ws;
		getline(cin, s.department);
		cout << "Enter year: ";
		cin >> s.year;
	}

	void PrintStudentData(const Student &s)
	{
		cout << "Name: " << s.name << endl;
		cout << "Age: " << s.age << endl;
		cout << "Department: " << s.department << endl;
		cout << "Year: " << s.year << endl
			 << endl;
	}
}

int main()
{
	int N;
	cout << "Enter the number of students: ";
	cin >> N;
	StudentSystem::Student s[N];
	for (int i = 0; i < N; i++)
	{
		cout << "Enter details of Student " << (i + 1) << ": " << endl;
		StudentSystem::ReadStudentData(s[i]);
	}
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "Details of Student " << (i + 1) << ": " << endl;
		StudentSystem::PrintStudentData(s[i]);
	}
	return 0;
}
