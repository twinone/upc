#include <iostream>
#include <math.h>

/**
Statement:
Write a program that reads a number x and a polynomial p(z) = c0 z0 + c1 z1 + ⋯ + cn zn, and computes p(x).

Input

Input consists of a real number x followed by the description of the polynomial p(z): the real coefficients c0, c1, …, cn in this order. (The first sample input/output corresponds to the evaluation of p(z) = 3 + 4z + 5z2 at x = 2.)

Output

Print p(x) with 4 digits after the decimal point.
*/

using namespace std;

// Calculates base to the exp'th
// Okay, that's too slow, let's just use math.h's pow function...
// double pow(double base, int exp) {
// 	double res = 1;
// 	for (int i = 0; i < exp; i++) {
// 		res *= base;
// 	}
// 	return res;
// }

int main() {
	
	double result = 0;
	double x, tmp;
	cin >> x;

	for (int i = 0; cin >> tmp; i++) {
		result += tmp * pow(x, i);
	}


	cout.setf(ios::fixed);
	cout.precision(4);

	cout << result << endl;

	return 0;
}


