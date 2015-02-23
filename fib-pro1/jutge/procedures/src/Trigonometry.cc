#include <iostream>
#include <math.h>

/**
Statement:
Write a program that reads a sequence of angles in degrees, and prints their sine and their cosine.

Input

Input consists of a sequence of real numbers that represent angles in degrees.

Output

For each given angle, print a line with its sine and its cosine. Print all the numbers with six digits after the decimal point.

Observation

Use the procedures that your programming language already provides to compute sines and cosines.
*/

using namespace std;

int main() {
	cout.setf(ios::fixed);
	cout.precision(6);

	double deg;
	while (cin >> deg) {
		double rad = deg * M_PI / 180;
		cout << sin(rad) << " " << cos(rad) << endl;
	}

	return 0;
}


