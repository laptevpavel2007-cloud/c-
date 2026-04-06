#include <iostream>
#include <cmath>
#include "Header.h"


int nods(int a, int b) {
	while (b) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
};

bool Rational::perfect_sqrt() const {
	if (num < 0) {
		return false;
	}

	int sqrt_num = (int)sqrt(num);
	int sqrt_den = (int)sqrt(den);

	return (sqrt_num * sqrt_num == num) && (sqrt_den * sqrt_den == den);
}

Rational Rational::sqrt_f() {
	Rational c(*this);

	if (c.num < 0) {
		cout << "It is impossible to find the root of a number less than 0" << endl;
		return Rational(0);
	};

	if (c == Rational(0)) {
		return Rational(0);
	};

	if (perfect_sqrt()) {
		int sqrt_num = (int)sqrt(num);
		int sqrt_den = (int)sqrt(den);
		return Rational(sqrt_num, sqrt_den);
	}
	else {
		Rational x_0;
		bool flag = false;
		for (int n = 0; flag != true; n++) {
			Rational x_0(n);
			if (x_0 * x_0 > c) {
				if (n > 0) {
					x_0 = Rational(n - 1);
				}
				else {
					x_0 = Rational(0);
				}
				flag = true;
			}
		};
		Rational x = x_0;
		Rational const_two(2);
		for (int i = 0; i < 20; i++) {
			if (x == Rational(0)) {
				x = Rational(1);
			};

			Rational x_next = (x + c / x) / const_two;
			x = x_next;
		};
		return x;
	}
};

Rational::Rational() {
	num = 0;
	den = 1;
};

Rational::Rational(int n) {
	num = n;
	den = 1;
};

Rational::Rational(int n, int d) {
	num = n;
	den = d;
	simplify();
};

void Rational::simplify() {
	int nod = nods(abs(num), abs(den));
	if (nod != 0) {
		num /= nod;
		den /= nod;
	}
	if (den < 0) {
		num = -num;
		den = -den;
	}
};

Rational& Rational::operator +=(const Rational& r) {
	num = num * r.den + den * r.num;
	den = den * r.den;
	simplify();

	return *this;
};

Rational Rational::operator +(const Rational& r) const {
	Rational c(*this);
	c += r;
	return c;
};

Rational Rational::operator -() const {
	Rational r(-num, den);
	return r;
};

Rational& Rational::operator -=(const Rational& r) {
	return (*this += (-r));
};

Rational& Rational::operator ++() {
	num += den;
	return *this;
};

Rational Rational::operator ++(int) {
	Rational r(*this);
	num += den;
	return r;
};

Rational& Rational::operator *=(const Rational& r) {
	num = num * r.num;
	den = den * r.den;
	simplify();

	return *this;
};

Rational Rational::operator *(const Rational& r) const {
	Rational c(*this);
	c *= r;
	return c;
};

Rational& Rational::operator /=(const Rational& r) {
	if (r.num == 0) {
		cout << "It cannot be divided by 0" << endl;
		return *this;
	}
	else {
		num = num * r.den;
		den = den * r.num;
		simplify();

		return *this;
	}
};

Rational Rational::operator /(const Rational& r) const {
	Rational c(*this);
	c /= r;

	return c;
};

bool Rational::operator ==(const Rational& r) const {
	return (num == r.num) && (den == r.den);
};

bool Rational::operator !=(const Rational& r) const {
	return !(*this == r);
};

bool Rational::operator >(const Rational& r) const {
	return (num * r.den > r.num * den);
};

bool Rational::operator <(const Rational& r) const {
	return (num * r.den < r.num * den);
};

void equation(const Rational& a, const Rational& b, const Rational& c) {
	const Rational const_four(4);
	const Rational const_two(2);
	const Rational const_zero(0);

	Rational d = (b * b + (-(const_four * a * c)));
	
	if (d < const_zero) {
		cout << "There is no solution" << endl;
	}

	else if (d == const_zero) {
		cout << "x = " << ((-b) / (const_two * a)) << endl;
	}

	else if (d > const_zero) {
		Rational sqrt_d = d.sqrt_f();
		cout << "x1 = " << (((-b) + sqrt_d) / (const_two * a)) << " x2 = " << (((-b) + (-(sqrt_d))) / (const_two * a)) << endl;
	}

};

istream& operator >>(istream& in, Rational& r) {
	in >> r.num >> r.den;
	return in;
};

ostream& operator <<(ostream& out, const Rational& r) {
	out << r.num << "/" << r.den;
	return out;
};