#include <iostream>

/**
Statement:
We define the valencia of a natural number n as the absolute value of the substraction between the sum of the digits that are in odd positions and the sum of the digits that are in even positions (the positions are counted starting in one and from the right to the left). n is balanced if its valencia is 0.

For instance 15741 is a balanced number, because the sum of the digits that are in odd positions and the sum of the digits that are in even positions is 9, therefore it has valencia 0. However, 31 is not a balanced number, because its valencia is 2.

Your task is to write a program that, given a non empty sequence of natural numbers, prints the first balanced number of the sequence. If there is not any balanced number, print the greatest valencia of the numbers in the sequence.

Input

The input is a non empty sequence of natural numbers.

Output

Your program must print a line with the first balanced number of the sequence. If there is not any, print the greatest valencia of the sequence. Follow the format of the instances.

Observation

Your program must implement and use the function

     int valencia(int n);
that, given a natural number |n|, returns its valencia.
*/

using namespace std;


int valencia(int n) {
	int sign = 1;
	int v = 0;
	while (n > 0) {
		v += (n % 10) * sign;
		n /= 10;
		sign *= -1;
	}
	if (v < 0) return -1 * v;
	return v;
}

int main() {

	int x;
	int max = 0;
	bool solved = false;
	while (cin >> x && !solved) {
		int v = valencia(x);
		if (v == 0) {
			cout << "The first balanced number is " << x << "." << endl;
			solved = true;
		}
		else if (v > max) max = v;
	}
	if (!solved) cout << "The greatest valencia is " << max << "." << endl;


	return 0;
}


