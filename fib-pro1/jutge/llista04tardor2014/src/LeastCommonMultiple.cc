#include <iostream>

/**
Statement:
Write a program such that, given n strictly positive natural numbers x1 … xn, prints their least common multiple greater than zero.

Input

Input consists of several cases. Each case begins with a number n ≥ 1, followed by x1 … xn. A special case with n = 0 marks the end of input.

Output

For every case, print in a line the least common multiple greater than zero of x1 … xn. For the given cases, this number will always be between 1 and 109.
*/

using namespace std;


/* Standard C Function: Greatest Common Divisor */
int gcd( int a, int b ) {
	int c;
	while (a != 0) {
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

int lcm(int a, int b) {
	return a / gcd(a, b) * b;
}


int main() {
	
	int x = 1; // enter loop
	while (x != 0) {
		cin >> x;
		if (x != 0) {
			int l;
			cin >> l;
			for (int i = 0; i < x-1; i++) {
				int y;
				cin >> y;

				l = lcm(l, y);

			}

		// cout << "Result: " << l << endl;
			cout << l << endl;
		}
	}


	return 0;
}


