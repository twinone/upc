#include <iostream>

/**
Statement:
Write a program that reads three numbers, all different, and prints their maximum.

Input

Input consists of three different integer numbers.

Output

Print a line with the maximum of the three numbers.
*/

using namespace std;

int main() {
	int a, b, c, max;
	cin >> a >> b >> c;
	if (a > b && a > c) {
		max = a;
	} else {
		max = b > c ? b : c;
	}
	cout << max << endl;
	return 0;
}


