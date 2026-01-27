#include <iostream>
using namespace std;

namespace Utility
{
    template <typename T>
    void swap_elements(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }
    struct Point
    {
        int x;
        int y;
    };
}

int main()
{
    int i1 = 10, i2 = 20;
    cout << "Int before: " << i1 << ", " << i2 << endl;
    Utility::swap_elements(i1, i2);
    cout << "Int after:  " << i1 << ", " << i2 << "\n"
         << endl;

    short s1 = 5, s2 = 99;
    cout << "Short before: " << s1 << ", " << s2 << endl;
    Utility::swap_elements(s1, s2);
    cout << "Short after:  " << s1 << ", " << s2 << "\n"
         << endl;

    float f1 = 1.5f, f2 = 3.14f;
    cout << "Float before: " << f1 << ", " << f2 << endl;
    Utility::swap_elements(f1, f2);
    cout << "Float after:  " << f1 << ", " << f2 << "\n"
         << endl;

    double d1 = 9.999, d2 = 0.001;
    cout << "Double before: " << d1 << ", " << d2 << endl;
    Utility::swap_elements(d1, d2);
    cout << "Double after:  " << d1 << ", " << d2 << "\n"
         << endl;

    Utility::Point p1 = {1, 1};
    Utility::Point p2 = {99, 99};
    cout << "Struct before: P1(" << p1.x << "," << p1.y << ") | P2(" << p2.x << "," << p2.y << ")" << endl;
    Utility::swap_elements(p1, p2);
    cout << "Struct after:  P1(" << p1.x << "," << p1.y << ") | P2(" << p2.x << "," << p2.y << ")" << endl;

    return 0;
}