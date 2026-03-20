#include <iostream>

using namespace std;

namespace Complex
{
    class ComplexNumber
    {
    private:
        double real;
        double imag;

    public:
        ComplexNumber(double r = 0, double i = 0) : real(r), imag(i) {}

        friend ComplexNumber operator+(const ComplexNumber &c1, const ComplexNumber &c2)
        {
            return ComplexNumber(c1.real + c2.real, c1.imag + c2.imag);
        }

        ComplexNumber operator-(const ComplexNumber &c2)
        {
            return ComplexNumber(real - c2.real, imag - c2.imag);
        }

        void display() const
        {
            if (imag >= 0)
                cout << real << " + " << imag << "i" << endl;
            else
                cout << real << " - " << -imag << "i" << endl;
        }
    };
}

int main()
{
    using namespace Complex;
    ComplexNumber c1(5.5, 3.2);
    ComplexNumber c2(2.2, 1.1);

    cout << "Complex Number 1: ";
    c1.display();

    cout << "Complex Number 2: ";
    c2.display();

    ComplexNumber sum1 = c1 + 9;
    cout << "\nResult of c1 + 9: ";
    sum1.display();

    ComplexNumber sum2 = 9 + c1;
    cout << "Result of 9 + c1: ";
    sum2.display();

    ComplexNumber sum = c1 + c2;
    cout << "\nResult of c1 + c2: ";
    sum.display();

    ComplexNumber diff = c1 - c2;
    cout << "\nResult of c1 - c2: ";
    diff.display();

    return 0;
}