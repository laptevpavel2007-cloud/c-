#include <iostream>
#include <cmath>

using namespace std;

class Rational {
private:
	void simplify();

public:
	
	int num;
	int den;
	Rational();
	Rational(int n);
	Rational(int n, int d);

	Rational& operator +=(const Rational& r);
	Rational operator +(const Rational& r) const;

	Rational& operator -=(const Rational& r);
	Rational operator -() const;

	Rational& operator ++();
	Rational operator ++(int);

	Rational& operator *=(const Rational& r);
	Rational operator *(const Rational& r) const;

	Rational& operator /=(const Rational& r);
	Rational operator /(const Rational& r) const;

	bool operator ==(const Rational& r) const;
	bool operator !=(const Rational& r) const;

	bool operator >(const Rational& r) const;
	bool operator <(const Rational& r) const;

	friend istream& operator >>(istream& in, Rational& r);
	friend ostream& operator <<(ostream& out, const Rational& r);

	bool perfect_sqrt() const;
	Rational sqrt_f();

};

void equation(const Rational& a, const Rational& b, const Rational& c);