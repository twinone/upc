#include <iostream>
#include <math.h>

/**
Statement:
Write a program that reads a sequence of natural numbers, and prints the square and the square root of each one.

Input

Input consists of a sequence of natural numbers.

Output

For every given number, print in a line its square, and its square root with six digits after the decimal point.

Observation

Use the procedure that your programming language already provides to compute square roots.
*/

using namespace std;

int main() {
	cout.setf(ios::fixed);
	cout.precision(6);

	double x;
	while (cin >> x) {
		cout << int(x * x) << " " << sqrt(x) << endl; 
	}

	return 0;
}


