#include <iostream>

/**
Statement:
Write a program that reads several numbers and prints the sum of the digits of each one.

Input

Input consists of a sequence of natural numbers.

Output

For every number, print the sum of its digits following the format of the example.
*/

using namespace std;

int sumDigits(int a) {
	int sum = 0;
	while (a > 0) {
		sum += a % 10;
		a /= 10;
	}
	return sum;
}

int main() {
	int x;
	while (cin >> x) {
		cout << "The sum of the digits of "<<x<<" is "<<sumDigits(x)<<"." << endl;
	}

	return 0;
}


