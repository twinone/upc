#include <iostream>

/**
Statement:
Write a program that reads two numbers and prints their maximum.

Input

Input consists of two integer numbers.

Output

Print a line with the maximum of the two numbers.
*/

using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	cout << (a > b ? a : b) << endl;
	return 0;
}


