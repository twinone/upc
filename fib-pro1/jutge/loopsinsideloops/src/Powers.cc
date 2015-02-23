#include <iostream>

/**
Statement:
Write a program to compute powers.

Input

Input consists of several pairs of integer numbers a and b. Assume b ≥ 0.

Output

For every pair a,b, print ab. Supose, as usual, that 00 = 1.
*/

using namespace std;

int pow(int a, int b) {
	if (b == 0) { return 1; }
	int r = 1;
	for (int i = 0; i < b; i++) {
		r *= a;
	}
	return r;
}

int main() {
	int a, b;
	while (cin >> a >> b)
		cout << pow(a, b) << endl;

	return 0;
}


