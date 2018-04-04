#include <iostream>

/**
Statement:
Write a program that, given two intervals, computes the interval corresponding to their intersection, or tells that it is empty.

Input

Input consists of four integer numbers a1, b1, a2, b2 that represent the intervals [a1,b1] and [a2,b2]. Assume a1≤ b1 and a2≤ b2.

Output

Print “[]” if their intersection is empty, or “[x,y]” if this is their non-empty intersection.
*/

using namespace std;

int main() {
	int a1, b1, a2, b2;
	cin >> a1 >> b1 >> a2 >> b2;

	int x = a1>a2?a1:a2;
	int y = b1<b2?b1:b2;
	if (x > y) {
		cout << "[]" << endl;
	} else {
		cout << "[" << x << "," << y << "]" << endl;
	}

	return 0;
}


