#include <iostream>
#include <string>
#include <limits>

namespace CompanySystem
{
    class Person
    {
    protected:
        std::string name;
        int age;
        std::string gender;

    public:
        Person(const std::string &n = "Unknown", int a = 0, const std::string &g = "Unknown")
            : name(n), age(a), gender(g) {}

        virtual ~Person() {}

        virtual void display() const
        {
            std::cout << "Name: " << name << ", Age: " << age << ", Gender: " << gender << "\n";
        }

        virtual void readData();
    };

    class Employee : virtual public Person
    {
    protected:
        int empID;
        double salary;

    public:
        Employee(const std::string &n = "Unknown", int a = 0, const std::string &g = "Unknown",
                 int id = 0, double sal = 0.0)
            : Person(n, a, g), empID(id), salary(sal) {}

        void display() const override
        {
            Person::display();
            std::cout << "EmpID: " << empID << ", Salary: $" << salary << "\n";
        }

        void readData() override;
    };

    class TechnicalStaff : virtual public Person
    {
    protected:
        std::string department;
        std::string skillSet;

    public:
        TechnicalStaff(const std::string &n = "Unknown", int a = 0, const std::string &g = "Unknown",
                       const std::string &dept = "None", const std::string &skills = "None")
            : Person(n, a, g), department(dept), skillSet(skills) {}

        void display() const override
        {
            Person::display();
            std::cout << "Department: " << department << ", Skills: " << skillSet << "\n";
        }

        void readData() override;
    };

    class SystemAdmin : public Employee
    {
    private:
        std::string workLoad;

    public:
        SystemAdmin(const std::string &n = "Unknown", int a = 0, const std::string &g = "Unknown",
                    int id = 0, double sal = 0.0, const std::string &wl = "Normal")
            : Person(n, a, g), Employee(n, a, g, id, sal), workLoad(wl) {}

        void display() const override
        {
            Employee::display(); // Prints Person + Employee data
            std::cout << "Workload: " << workLoad << "\n";
        }

        void readData() override;
    };

    class Trainee : public TechnicalStaff
    {
    private:
        int durationMonths;
        double stipend;

    public:
        Trainee(const std::string &n = "Unknown", int a = 0, const std::string &g = "Unknown",
                const std::string &dept = "None", const std::string &skills = "None",
                int dur = 0, double stip = 0.0)
            : Person(n, a, g), TechnicalStaff(n, a, g, dept, skills), durationMonths(dur), stipend(stip) {}

        void display() const override
        {
            TechnicalStaff::display(); // Prints Person + TechStaff data
            std::cout << "Duration: " << durationMonths << " months, Stipend: $" << stipend << "\n";
        }

        void readData() override;
    };

    class Developer : public Employee, public TechnicalStaff
    {
    private:
        std::string project;
        int yearsOfExperience;

    public:
        Developer(const std::string &n = "Unknown", int a = 0, const std::string &g = "Unknown",
                  int id = 0, double sal = 0.0,
                  const std::string &dept = "None", const std::string &skills = "None",
                  const std::string &proj = "None", int yoe = 0)
            : Person(n, a, g),
              Employee(n, a, g, id, sal),
              TechnicalStaff(n, a, g, dept, skills),
              project(proj), yearsOfExperience(yoe) {}

        void display() const override;
        void readData() override;
    };

    void Person::readData()
    {
        std::cout << "Enter Name: ";
        std::getline(std::cin >> std::ws, name);
        std::cout << "Enter Age: ";
        std::cin >> age;
        std::cout << "Enter Gender: ";
        std::cin >> gender;
    }

    void Employee::readData()
    {
        Person::readData();
        std::cout << "Enter Employee ID: ";
        std::cin >> empID;
        std::cout << "Enter Salary: ";
        std::cin >> salary;
    }

    void TechnicalStaff::readData()
    {
        Person::readData();
        std::cout << "Enter Department: ";
        std::getline(std::cin >> std::ws, department);
        std::cout << "Enter Skillset: ";
        std::getline(std::cin >> std::ws, skillSet);
    }

    void SystemAdmin::readData()
    {
        Employee::readData();
        std::cout << "Enter Workload (e.g., High, Medium, Low): ";
        std::getline(std::cin >> std::ws, workLoad);
    }

    void Trainee::readData()
    {
        TechnicalStaff::readData();
        std::cout << "Enter Duration (in months): ";
        std::cin >> durationMonths;
        std::cout << "Enter Stipend: ";
        std::cin >> stipend;
    }

    void Developer::display() const
    {
        Person::display();
        std::cout << "EmpID: " << empID << ", Salary: $" << salary << "\n"
                  << "Department: " << department << ", Skills: " << skillSet << "\n"
                  << "Project: " << project << ", YOE: " << yearsOfExperience << " years\n";
    }

    void Developer::readData()
    {
        Person::readData();
        std::cout << "Enter Employee ID: ";
        std::cin >> empID;
        std::cout << "Enter Salary: ";
        std::cin >> salary;
        std::cout << "Enter Department: ";
        std::getline(std::cin >> std::ws, department);
        std::cout << "Enter Skillset: ";
        std::getline(std::cin >> std::ws, skillSet);
        std::cout << "Enter Project Name: ";
        std::getline(std::cin >> std::ws, project);
        std::cout << "Enter Years of Experience: ";
        std::cin >> yearsOfExperience;
    }

}

using namespace CompanySystem;

int main()
{
    std::cout << "--- Creating Developer ---\n";
    Developer dev("Alice", 28, "Female", 101, 85000.0, "IT", "C++, Python", "AI Migration", 5);
    dev.display();

    std::cout << "\n--- Creating System Admin ---\n";
    SystemAdmin admin("Bob", 35, "Male", 102, 60000.0, "High");
    admin.display();

    std::cout << "\n--- Creating Trainee via readData() ---\n";
    Trainee trainee;
    trainee.readData();

    std::cout << "\n--- Trainee Profile ---\n";
    trainee.display();

    return 0;
}