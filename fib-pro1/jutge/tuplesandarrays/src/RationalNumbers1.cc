#include <iostream>

/**
Statement:
Using the definition

     struct Rational {
         int num, den;
     };
write a function

     Rational rational(int n, int d);
that returns an equivalent rational to n/d and “normalized” according to: if the numerator is 0, the denominator is 1; otherwise, the numerator and the denominator do not have any common factor, and the denominator is positive.

Precondition

d ≠ 0.

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



int main() {
	return 0;
}


