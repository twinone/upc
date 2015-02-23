#include <iostream>

/**
Statement:
Write an iterative function

     int gcd(int a, int b);
that computes the greatest common divisor of two natural numbers a and b using the fast version of the Euclidean algorithm.

Precondition

Neither a nor b are negative, and at least one of them is strictly greater than zero.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;


int gcd(int a, int b) {
	if (a == 0) return b;
	if (b == 0) return a;
	if (b > a) {
		int tmp = b;
		b = a;
		a = tmp;
	}
	// a is now always bigger as b
	// and a,b > 0

	// enter while
	int r = 1;
	
	while (r != 0) {
		r = a % b;
		a = b;
		b = r;
	}

	return a;
}

int main() {
	// Uncomment for testing
	// int a,b;
	// cin >> a >> b;
	// cout << gcd(a,b) << endl;

	return 0;
}


