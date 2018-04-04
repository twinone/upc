#include <iostream>

/**
Statement:
Your task is to write a program that computes the result of adding a sequence of fractions.

Using the definition

     struct Fraction {
         int num, den;   // always strictly positive
     };
your program must include and use the function

     Fraction addition(const Fraction& x, const Fraction& y);
that returns the addition of |x| and |y|, without common factors in the numerator and denominator.

Input

The input is a sequence of one or more simplified fractions separated by plus signs, ended with an equal sign. Each fraction consists of its numerator, a bar, and its denominator. Numerators and denominators are natural strictly positive.

Output

Your program must print the simplified fraction corresponding to the sum of all the given fractions.

Observations

In order to avoid overflows, use the function |addition()| to accumulate the partial calculations.
Inefficient calculation of the greatest common divisor will be negatively valued.
Using vectors is not allowed to solve this problem.
*/

using namespace std;

int calculate_gcd(int a, int b) {
	// Since we can't use do-while() constructs...
	int c = a % b;
	a = b;
	b = c;
	while (c != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

struct Fraction {
	int num, den; 	// always strictly positive
};

Fraction addition(const Fraction& x, const Fraction& y) {
	// cout << "Adding " << x.num << "/" << x.den << " and " << y.num << "/" << y.den << endl;
	Fraction f;
	f.den = x.den * y.den;
	f.num = x.num*y.den + y.num*x.den;
	int gcd = calculate_gcd(f.den, f.num);
	f.den /= gcd;
	f.num /= gcd;
	return f;
}

bool read_fraction(Fraction& f) {
	char c;
	return cin >> f.num >> c >> f.den;
}

int main() {
	char c;
	Fraction sum;
	read_fraction(sum);
	Fraction f;
	while (cin >> c and c != '=' and read_fraction(f)) sum = addition(sum, f); 

	cout << sum.num << "/" << sum.den << endl;
	return 0;
}


