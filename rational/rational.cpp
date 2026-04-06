#include "Header.h"
#include <iostream>

using namespace std;

int main()
{
    int num_a, den_a, num_b, den_b, num_c, den_c;

    cout << "Enter the numerator and denominator of the coefficient a (separated by a space)" << endl;
    cin >> num_a >> den_a;

    cout << "Enter the numerator and denominator of the coefficient b (separated by a space)" << endl;
    cin >> num_b >> den_b;

    cout << "Enter the numerator and denominator of the coefficient c (separated by a space)" << endl;
    cin >> num_c >> den_c;

    Rational a(num_a, den_a);
    Rational b(num_b, den_b);
    Rational c(num_c, den_c);

    equation(a, b, c);

    return 0;
}