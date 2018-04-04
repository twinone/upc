#include <iostream>

/**
Statement:
Write a program that prints squares with n2 n’s.

Input

Input consists of several natural numbers between 1 and 9.

Output

For every n, print a square of size n × n full of n’s. Separate two squares with an empty line.
*/

using namespace std;

int main() {
	int x;
	bool space = false;
	while (cin >> x) {

		// Add space if necessary
		if (space) cout << endl;
		else space = true;

		for (int i = 0; i < x; i++) {
			for (int j = 0; j < x; j++) {
				cout << x;
			}
			cout << endl;
		}
	}


	return 0;
}


