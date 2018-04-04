#include <iostream>

/**
Statement:
Write a program that reads two natural numbers a and b, with b > 0, and prints the integer division d and the remainder r of a divided by b.

Remember that, by definition, d i r must be the only integer numbers such that 0 ≤ r < b and d · b + r = a.

Input

Input consists of a and b, with b > 0.

Output

Print a line with the integer division and the remainder of a divided by b, separated by a space.

Observation

Although the conditions for the input of this exercise prevent divisions by zero, check what happens to your program in that case.
*/

using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	if (b == 0) {
		cerr << "Cannot divide by zero" <<endl;
		return -1;
	}

	int result = a / b;
	int remainder = a % b;

	cout << result << " " << remainder << endl;

	return 0;
}


