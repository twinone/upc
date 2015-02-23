#include <iostream>

/**
Statement:
Write a program that computes logarithms in several bases.

Input

Input consists of a sequence of pairs of natural numbers b and n, such that b≥ 2 and n≥ 1.

Output

For every pair, print ⌊ logb n ⌋.
*/

using namespace std;

int log(int base, int num) {
	int r = 0;
	while (num >= base) {
		num /= base;
		r++;
	}
	return r;
}

int main() {
	int a, b;	
	while (cin >> a >> b) cout << log(a, b) << endl;

	return 0;
}


