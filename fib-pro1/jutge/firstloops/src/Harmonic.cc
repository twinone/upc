#include <iostream>
#include <iomanip> // For setprecision()

/**
Statement:
Write a program that reads a number n and prints the n-th harmonic number, defined as Hn = 1/1 + 1/2 + ⋯ + 1/n.

Input

Input consists of a natural number n.

Output

Print Hn with 4 digits after the decimal point.
*/

using namespace std;

int main() {
	int x;
	cin >> x;

	double result = 0;
	for (int i = 1; i <= x; i++) {
		result += (double)1 / i;
	}

	cout << setprecision(4) << fixed << result << endl;

	return 0;
}


