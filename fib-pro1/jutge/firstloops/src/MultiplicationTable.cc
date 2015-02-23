#include <iostream>

/**
Statement:
Write a program that reads a number n and prints the “multiplication table” of n.

Input

Input consists of a natural number n between 1 and 9.

Output

Print the “multiplication table” of n.
*/

using namespace std;

int main() {
	int x;
	cin >> x;

	// Fix #1: Added spacing around "=" sign
	for (int i = 1; i <= 10; i++) {
		cout << x << "*" << i << " = " << (x*i) << endl;
	}


	return 0;
}


