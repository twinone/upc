#include <iostream>

/**
Statement:
Write a program that reads several numbers, and for each one prints the product of its digits, and the product of the digits of the latest product, etcetera, until the resulting product has just one digit.

Input

Input consists of several natural numbers.

Output

For every number, print the product of the digits of the number, the product of the digits of the previous product, etcetera, one per line, until the resulting product has just one digit. Print a line with 10 dashes after the output for every number.
*/

using namespace std;

long multiplyDigits(int a) {
	long prod = 1;
	while (a / 10 > 0) {
		prod *= a % 10;
		a /= 10;
	}
	// add remainder:
	prod *= a;
	return prod;
}

int main() {
	long x;
	while (cin >> x) {
		bool once = true;
		while (x > 9 || once) {
			once = false;
			long prod = multiplyDigits(x);
			cout << "The product of the digits of "<< x <<" is "<< prod <<"." << endl;
			x = prod;
		}
		cout << "----------" << endl;
	}

	return 0;
}


