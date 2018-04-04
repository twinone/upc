#include <iostream>
#include <stdlib.h>

/**
Statement:
Write a program that reads sequences of natural numbers, and that for each one prints the number of pairs of consecutive numbers such that the second number of the pair is greater than the first one.

Input

Input consists of a natural number n, followed by n sequences of strictly positive natural numbers. Each sequence ends with a zero.

Output

For every sequence, print in a line the number of pairs of consecutive numbers such that the second number of the pair is greater than the first one.


*/

using namespace std;

int main() {

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int total = 0;
		int old;
		cin >> old;

		int r = old;
		while (r != 0) {
			if (r > old) total++;
			old = r;
			cin >> r;
		}
		cout << total << endl;
	}

	return 0;
}


