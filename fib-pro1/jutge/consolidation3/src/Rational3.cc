#include <iostream>

/**
Statement:
Using the same definition of the rational numbers that in the exercise : “”, write the functions

     Rational sum(const Rational& a, const Rational& b);
     Rational substraction(const Rational& a, const Rational& b);
     Rational product(const Rational& a, const Rational& b);
     Rational division(const Rational& a, const Rational& b);
that returns respectively the sum, the substraction, the product and the division of two rational numbers given, “normalized” according to the same convention that in the exercise : “”.

Write also the procedure

     void adds_one(Rational& r);
that adds an unit to the rational number r.

Precondition

The rational numbers a and b are correct and normalized. In the case of division, b ≠ 0.

Observation You only need to submit the required classes; your main program will be ignored. Strictly obey the type definitions of the statement.


*/

using namespace std;

struct Rational {
	int num, den;
};

int f_gcd(int a, int b) {
	int c;
	while (a != 0) {
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}
void normalize(Rational& r) {
	int gcd = f_gcd(r.num , r.den);
	r.num/=gcd;
	r.den/=gcd;
	if (r.den < 0) {
		r.num *= -1;
		r.den *= -1;
	}
}

Rational sum(const Rational& a, const Rational& b) {
	Rational r;
	r.num = a.num * b.den + a.den * b.num;
	r.den = a.den * b.den;
	normalize(r);
	return r;
}

Rational substraction(const Rational& a, const Rational& b) {
	Rational r;
	r.num = a.num * b.den - a.den * b.num;
	r.den = a.den * b.den;
	normalize(r);
	return r;
}

Rational product(const Rational& a, const Rational& b) {
	Rational r;
	r.num = a.num * b.num;
	r.den = a.den * b.den;
	normalize(r);
	return r;
}

Rational division(const Rational& a, const Rational& b) {
	Rational r;
	r.num = a.num * b.den;
	r.den = a.den * b.num;
	normalize(r);
	return r;
}


void adds_one(Rational& r) {
	r.num += r.den;
	normalize(r);
}
void print_rational(Rational& r) {
	cout << r.num << "/" << r.den << endl;
}

int main() {
	Rational a, b;
	cin >> a.num >> a.den >> b.num >> b.den;

	Rational s = sum(a, b);
	Rational sub = substraction(a, b);
	Rational m = product(a, b);
	Rational d = division(a, b);

	print_rational(s);
	print_rational(sub);
	print_rational(m);
	print_rational(d);

	return 0;
}


