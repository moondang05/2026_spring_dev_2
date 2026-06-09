#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    float a;
    float b;
    cin >> a >> b;
    cout << fixed << setprecision(2);
    cout << a << " + " << b << " = " << a + b << '\n';
    cout << a << " - " << b << " = " << a - b << '\n';
    cout << a << " * " << b << " = " << a * b << '\n';
    cout << a << " / " << b << " = " << a / b << '\n';

    return 0;
}