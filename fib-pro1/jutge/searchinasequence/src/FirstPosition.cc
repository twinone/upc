#include <iostream>

/**
Statement:
Write a program that reads a sequence of natural numbers and prints the position of the first even number.

Input

Input consists of a sequence of natural numbers that contains, at least, one even number.

Output

Print the position of the first even number of the sequence.
*/

using namespace std;

int main() {
	int x;
	int i = 1;
	while (cin >> x && x % 2 != 0) i++;
	cout << i << endl;

	return 0;
}


