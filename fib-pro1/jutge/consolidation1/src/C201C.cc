#include <iostream>

/**
Statement:
Your task is to write a program that reads an integer strictly positive x and a sequence of integers, and prints how many elements of the sequence are multiple of x.

Input

The input is an integer x > 0 followed by a sequence of integers.

Output

Your program must print the number of elements of the sequence that are multiple of x.
*/

using namespace std;

int main() {
	long x, tmp, sum = 0;
	cin >> x;

	while (cin >> tmp) {
		if (tmp % x == 0) sum++;
	}

	cout << sum << endl;

	return 0;
}


