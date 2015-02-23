#include <iostream>

/**
Statement:
Write a function

     int reduction_of_digits(int x);
that, given a natural number x, returns the reduction of its digits.

In this exercise, we say that reducing the digits of a number means computing the sum of its digits. If the sum has just one digit, this is already the result. Otherwise, we apply the same process again to the sum, until we get a single digit.

Solve this problem using a recursive function

     int sum_of_digits(int x);
to return the sum of the digits of a natural number x.

Precondition

x is a natural number.

Observation

Although there is a mathematic trick to solve this problem faster than by adding up its digits, do not use it here.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;
int sum_of_digits(int x);

int reduction_of_digits(int x) {
	while (x >= 10) x = sum_of_digits(x);
	return x;
}

int sum_of_digits(int x) {
	if (x < 10) return x;
	return sum_of_digits(x/10) + x%10;
}

int main() {
	int x; cin >> x; cout << reduction_of_digits(x) << endl;
	return 0;
}


