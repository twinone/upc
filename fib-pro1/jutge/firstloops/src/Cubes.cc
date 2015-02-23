#include <iostream>

/**
Statement:
Write a program that reads a number n, and prints 03,13,…,(n−1)3,n3.

Input

Input consists of a natural number n.

Output

Print a line with 03,13,…,(n−1)3,n3. Separate the numbers with commas.
*/

using namespace std;

// This will overflow to negative results if you provide a big number...
int main() {
	int x;
	cin >> x;
	bool comma = false;
	for (int i = 0; i <= x; i++) {
		if (comma) cout << ","; else comma = true;
		cout << (long)(i*i*i);
	}
	cout <<endl;

	return 0;
}


