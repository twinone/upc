#include <iostream>

/**
Statement:
Let n be any strictly positive natural number. Consider the following process. If n is an even number, we divide it by two. Otherwise, we multiply it by 3 and add 1 to it. When we reach 1, we stop. For instance, starting with 3, we obtain the sequence

3,  10,  5,  16,  8,  4,  2,  1 .
Since 1937 it is conjectured that this process ends for any initial n, although nobody has been able to prove it. In this problem, we do not ask you for a proof. You only have to write a program that prints the number of steps that it takes to reach 1 for every given n.

Input

Input consists of several natural numbers n ≥ 1.

Output

For every n, print how many steps are needed to reach 1. Suppose that this number is well defined, that is, that the conjecture of the statement is true.
*/

using namespace std;

int main() {

	int x;
	while (cin >> x) {
		int count = 0;
		while (x != 1) {
			if (x % 2 == 0) x /= 2;
			else x = x * 3 + 1;
			count++;
		}
		cout << count << endl;
	}
	return 0;
}


