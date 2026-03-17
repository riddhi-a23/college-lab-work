#include <iostream>

using namespace std;

class ComplexNumber {
private:
    double real;
    double imag;

public:
    ComplexNumber(double r = 0, double i = 0) : real(r), imag(i) {}

    friend ComplexNumber operator+(const ComplexNumber& c1, const ComplexNumber& c2) {
        return ComplexNumber(c1.real + c2.real, c1.imag + c2.imag);
    }

    friend ComplexNumber operator-(const ComplexNumber& c1, const ComplexNumber& c2) {
        return ComplexNumber(c1.real - c2.real, c1.imag - c2.imag);
    }

    void display() const {
        if (imag >= 0)
            cout << real << " + " << imag << "i" << endl;
        else
            cout << real << " - " << -imag << "i" << endl;
    }
};

int main() {
    ComplexNumber c1(5.5, 3.2);

    cout << "Complex Number 1: ";
    c1.display();

    ComplexNumber sum1 = c1 + 9;
    cout << "\nResult of c1 + 9: ";
    sum1.display();

    ComplexNumber sum2 = 9 + c1;
    cout << "Result of 9 + c1: ";
    sum2.display();

    ComplexNumber diff1 = c1 - 4.5;
    cout << "\nResult of c1 - 4.5: ";
    diff1.display();

    ComplexNumber diff2 = 10 - c1;
    cout << "Result of 10 - c1: ";
    diff2.display();

    return 0;
}