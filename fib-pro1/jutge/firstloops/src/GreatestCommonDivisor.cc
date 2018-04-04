#include <iostream>

/**
Statement:
Write a program that computes the greatest common divisor of two numbers.

Input

Input consists of two strictly positive natural numbers a and b.

Output

Print the greatest common divisor of a and b.

Observation

Although the solution to this exercise does not need to be very efficient, it should not be too slow.
*/

using namespace std;


/* Standard C Function: Greatest Common Divisor */
int gcd(int a, int b ) {
	int c;
	while (a != 0) {
		c = a;
		a = b % a;
		b = c;
	}
	return b;
}

int main() {
	int a, b;
	cin >> a >> b;
	cout << "The gcd of " << a << " and " << b << " is " << gcd(a, b) << "." << endl;
	return 0;
}


