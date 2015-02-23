#include <iostream>

/**
Statement:
Write a function

     int gcd4(int a, int b, int c, int d);
that computes the greatest common divisor of four natural numbers a, b, c and d using the fast version of the Euclidean algorithm.

Precondition

The four numbers are strictly greater than zero.

Observation You only need to submit the required procedure; your main program will be ignored.

Hint

Using the function gcd(a, b) of the exercise P88790: “Iterative greatest common divisor” should be useful.


*/
using namespace std;

int gcd(int a, int b) {
	int c;
	while (a != 0) {
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

int gcd4(int a, int b, int c, int d) {
	return gcd(gcd(a, b), gcd(c, d));
}

int main() {
	return 0;
}


