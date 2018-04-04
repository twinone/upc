#include <iostream>

/**
Statement:
Write a program that, given an integer number i and a sequence of natural numbers x1, …, xn, prints xi.

Input

Input begins with an integer number i, followed by the sequence x1, …, xn.

Output

If the position i is correct, print the content of i as it is shown in the examples. Otherwise, print “Incorrect position.”.


*/

using namespace std;

int main() {
	int i, x;
	cin >> i;
	int p = 1;
	bool found = false;
	if (i > 0) {
		while (cin >> x) {
			if (p == i) {
				cout << "At the position " << p << " there is a(n) " << x << "." << endl;
				found = true;
				break;
			}
			p++;
		}
	}

	if (!found) cout << "Incorrect position." << endl;



	return 0;
}


