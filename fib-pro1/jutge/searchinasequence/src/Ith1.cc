#include <iostream>

/**
Statement:
Write a program that, given an integer number i and a sequence of natural numbers x1, …, xn, prints xi.

Input

Input begins with a number i, followed by the sequence x1, …, xn ended with −1. It is known that 1 ≤ i ≤ n.

Output

Print the content of the position i as it is shown in the examples.
*/

using namespace std;

int main() {
	int x;
	cin >> x;

	int n;
	for (int i = 1; i <= x; i++) {
		cin >> n;
	}
	cout << "At the position " << x << " there is a(n) "<<n<<"." << endl;

	return 0;
}


