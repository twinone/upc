#include <iostream>
#include <string>

/**
Statement:
Using the procedures done in the exercises : “”, : “” and : “”, your task is to write a program that reads a sequence of rational numbers and operations

r0    o1   r1    o2   r2    …    on − 1   rn − 1    on   rn    ,
and prints the result after each operation.

Input

Input consists of a line with an initial rational, followed by a sequence of lines, each one with a pair operation/rational. As in the exercise : “”, each rational is given by a pair of integer numbers, the second integer is not zero. The operations can be “add”, “substract”, “multiply” or “divide”. In this last case, the second rational is not zero.

Output

Your program must print the initial rational, followed by the accumulated result of each operation. Each rational number must be in a different line.


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

Rational read() {
	Rational r;
	cin >> r.num >> r.den;
	return r;
}
void print_rational(const Rational& r) {
	if (r.den == 1) cout << r.num << endl;
	else cout << r.num << "/" << r.den << endl;
}

int main() {
	Rational r = read();
	normalize(r);
	string s;
	while (cin >> s) {
		print_rational(r);
		if (s == "add") r = sum(r, read());
		else if (s == "substract") r = substraction(r, read());
		else if (s == "multiply") r = product(r, read());
		else  r = division(r, read());
	}
	print_rational(r);
	return 0;
}


