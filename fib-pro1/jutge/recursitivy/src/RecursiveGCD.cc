#include <iostream>

/**
Statement:
Write a recursive function

     int gcd(int a, int b);
that computes the greatest common divisor of two natural numbers a and b using the fast version of the Euclidean algorithm.

Precondition

Neither a nor b are negative, and at least one of them is strictly greater than zero.

Observation You only need to submit the required procedure; your main program will be ignored.


*/

using namespace std;

int gcd(int a, int b) {
	if (a == 0) return b;
	return gcd(b%a, a);
}


int main() {
	return 0;
}


