#include <iostream>

/**
Statement:
Write a program that reads sequences of natural numbers, and for each one tells if it has two elements such that their sum is an odd number.

Input

Input consists of several sequences, each one in a line. Each sequence consists of a natural number n, followed by n natural numbers x1, …, xn.

Output

For each input sequence, print “yes” or “no” depending on if it is possible to find two elements xi and xj (with i ≠ j) such that xi + xj is an odd number.
*/

using namespace std;

bool search_odd(int n) {
	bool even = false;
	bool odd = false;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		if (x%2 == 0) even = true;
		else odd = true;
		// if (even and odd) return true;
	}
	return odd and even;
}

int main() {
	int n;
	while (cin >> n) {
		cout << (search_odd(n) ? "yes" : "no") << endl;
	}


	return 0;
}


