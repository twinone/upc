#include <iostream>

/**
Statement:
Write a program that, given two intervals, tells if one is inside the other.

Input

Input consists of four integer numbers a1, b1, a2, b2 that represent the intervals [a1,b1] and [a2,b2]. Assume a1≤ b1 and a2≤ b2.

Output

Print ‘=’ if the intervals are equal, ‘1’ if the first is inside the second (but they are not equal), ‘2’ if the second is inside the first (but they are not equal), or ‘?’ otherwise.


*/

using namespace std;

int main() {
	int a1, b1, a2, b2;
	cin >> a1 >> b1 >> a2 >> b2;

	// Fix #1, "inside" includes borders.
	if (a1 == a2 && b1 == b2) {
		cout << "=" << endl;
	} else if (a1 <= a2 && b1 >= b2) {
		cout << 2 << endl;
	} else if (a1 >= a2 && b1 <= b2) {
		cout << 1 << endl;
	} else {
		cout << "?" << endl;
	}




	return 0;
}


