#include <iostream>

/**
Statement:
Write a program that reads a sequence of numbers, and prints the maximum quantity that can be obtained by adding numbers consecutively from the beginning, and the maximum quantity that can be obtained by adding numbers consecutively from the end.

Input

Input consists of several cases. Each case begins with a number n, followed by n integer numbers.

Output

For every case, print two numbers: the maximum quantity that can be obtained by adding zero or more consecutive numbers from the beginning, and the maximum quantity that can be obtained by adding zero or more consecutive numbers from the end.
*/

using namespace std;

int main() {
	int n;
	while (cin >> n) {
		int right_max, left_tot;
		int right_tot = 0;
		if (n > 0) {
			cin >> right_tot;
		}
		right_max = left_tot = right_tot;
		if (left_tot < 0) left_tot = 0;
		for (int i = 1; i < n; ++i) {
			int x;
			cin >> x;
			right_tot += x;
			if (right_tot >= right_max) right_max = right_tot;

			left_tot += x;
			if (left_tot <= 0) left_tot = 0;
		}
		if (right_max < 0) right_max = 0;
		cout << right_max << " " << left_tot << endl;

	}

	return 0;
}


