#include <iostream>

/**
Statement:
Write a program that reads sequences with all the numbers between 1 and n but one, and tells which one is missing.

Input

Input consists of several sequences. Every sequence begins with a number n between 1 and 104 followed by n − 1 natural numbers. Every number between 1 and n appears exactly once, except one of them, which is missing.

Output

For every sequence, print the missing number.
*/

using namespace std;

int main() {

	int n;
	while (cin >> n) {
		long total = (n*n + n)/2;
		// If we substract all numbers from the sum we get the missing one
		for (int i = 0; i < n-1; i++) {
			int x;
			cin >> x;
			total -= x;
		}
		cout << total << endl;
	}

	return 0;
}


