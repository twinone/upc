#include <iostream>

/**
Statement:
Write a program that reads a number n, and prints all numbers between 0 and n.

Input

Input consists of a natural number n.

Output

Print in order all natural numbers between 0 and n.
*/

using namespace std;

int main() {
	int x;
	cin >> x;

	for (int i = 0; i <= x; i++) {
		cout << i << endl;
	}

	return 0;
}


