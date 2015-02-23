#include <iostream>

/**
Statement:
Write a program that reads a natural number n, and prints 2n − 1 bars of asterisks, following the pattern that can be deduced from the examples.

Input

Input consists of a natural number n > 0.

Output

Print 2n − 1 lines, following the pattern that can be deduced from the examples.


*/

using namespace std;


void print(int n) {
	if (n == 1) cout << "*" << endl;
	else {
		for (int i = n; i > 0; --i) {
			for (int j = 0; j < i; ++j) cout << "*";
			cout << endl;
		}
		for (int i = 1; i < n; ++i) {
			print(i);
		}
	}
}
int main() {
	int n; cin >> n; print(n);
	return 0;
}


