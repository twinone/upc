#include <iostream>

/**
Statement:
Write a program that prints squares n × n. Draw each square independently, and start filling it with 0, 1, …, 9, 0, etc.

Input

Input consists of several natural numbers between 1 and 9.

Output

For every n, print a square of size n × n, by filling it with 0, 1, …, 9, 0, etc. Separate two squares with an empty line.
*/

using namespace std;

int main() {
	int x;
	bool space = false;
	while (cin >> x) {

		// Add space if necessary
		if (space) cout << endl;
		else space = true;
		int num = 0;
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < x; j++) {
				cout << (num++ % 10);
			}
			cout << endl;
		}
	}


	return 0;
}


