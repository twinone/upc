#include <iostream>

/**
Statement:
Write a program that reads two numbers x and y, and prints all numbers between x and y (or between y and x), in decreasing order.

Input

Input consists of two integer numbers x and y.

Output

Print all integer numbers between x and y (or between y and x), in decreasing order.
*/

using namespace std;

int main() {
	int a, b;
	int n, m;
	cin >> a >> b;

	n = a > b ? b : a; // small end
	m = a > b ? a : b; // big end


	while (m >= n) {
		cout << m-- << endl;
	}

	return 0;
}


