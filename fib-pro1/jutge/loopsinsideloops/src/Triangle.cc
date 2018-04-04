#include <iostream>

/**
Statement:
Write a program that, given a number n, prints a “triangle of size n”.

Input

Input consists of a natural number n.

Output

Print n lines, in such a way that the i-th line contains i asterisks.
*/

using namespace std;

int main() {
	int x;
	cin >> x;
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= i; j++) {
			cout << "*";
		}
		cout << endl;
	}


	return 0;
}


