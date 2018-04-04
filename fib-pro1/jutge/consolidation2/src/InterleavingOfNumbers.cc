#include <iostream>

/**
Statement:
We define the interleaving of two natural numbers with d digits x=xdxd−1… x2x1 and y=ydyd−1… y2y1 as xdydxd−1yd−1… x2y2x1y1. For example, the interleaving of 4123 and 5679 is 45162739. Write a program that reads pairs of natural numbers and prints their interleavings.

For the sake of practice, define and use a function

     int interleaving(int x, int y);
to compute the interleaving of two natural numbers x and y.

Input

Input consists of several pairs of natural numbers with the same number of digits.

Output

Print the interleaving of every given pair.

Observation

To avoid overflows, no given number will have more than four digits, but your program should not take this fact into account.
*/

using namespace std;

int interleaving(int x, int y) {
	int p = 1;
	int res = 0;
	while (x > 0 or y > 0) {
		res += p*(y%10);
		res += p*10*(x%10);
		x /= 10;
		y /= 10;
		p *= 100;
	}
	return res;
}

int main() {
	int x, y;
	while (cin >> x >> y) cout << interleaving(x, y) << endl;
	return 0;
}


