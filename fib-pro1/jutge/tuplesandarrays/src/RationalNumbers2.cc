#include <iostream>

/**
Statement:
Using the same definition of the rational numbers that in the exercise : “”, write a function with two output parameters:

     void read_rational(Rational& r, bool& end);
that tries to read a rational number represented by two integer numbers (the numerator and the denominator), returns the corresponding “normalized” rational according to the same convention that in the exercise : “”, and prints if the two integer have been read. end must be true if and only if have not been read (because the input has finished). The value of r is irrelevant when end is true.

Precondition

None of the read denominators will be 0.

Write also a procedure

     void print_rational(const Rational& r);
that prints the rational r with the format r.num/r.den, unless the denominator is 1, case in which print only the numerator. Do not print any intermediate space nor any jump line at the end.

Precondition

The rational r is correct and it is already normalized.

Observation You only need to submit the required classes; your main program will be ignored. Strictly obey the type definitions of the statement.


*/

using namespace std;

struct Rational {
	int num, den;
};

Rational rational(int n, int d) {
	Rational r;
	r.num = n;
	if (n == 0) r.den = 1;
	else r.den = d;
	return r;
}

void read_rational(Rational& r, bool& end) {
	if (not cin >> r.num or not cin >> r.den) end = true;
	else end = false;
}

void print_rational(const Rational& r) {
	if (r.den == 1) cout << r.num << endl;
	else cout << r.num << '/' << r.den << endl;
}

int main() {
	Rational r;
	bool end;
	read_rational(r, end);

	print_rational(r);
	// cout << "end: " << end << endl;
	return 0;
}


