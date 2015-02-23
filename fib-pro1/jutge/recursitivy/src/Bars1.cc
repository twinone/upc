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
		print(n-1);
		for (int i = 0; i < n; ++i) cout << "*";
		cout << endl;
		print(n-1);
 	}
}

int main() {
	int n;cin >> n; print(n);
	return 0;
}


