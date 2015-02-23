#include <iostream>

/**
Statement:
Write a program such that, given a number n, prints a “rhombus of size n”.

Input

Input consists of a natural number n ≥ 1.

Output

Print 2*n − 1 lines, as shown in the examples.
*/

using namespace std;

int main() {
	int x;
	cin >> x;

	int n = 2 * x - 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int numStars = i <= n / 2 ? i * 2 + 1 : (n - i - 1) * 2 + 1;
			int offset = (n - numStars) / 2;
			if (j >= offset && j < n - offset) {
				cout << "*";
			} else {
				cout << (j > offset ? "" :  " ");
			}

		}
		cout << endl;
	}


	return 0;
}


