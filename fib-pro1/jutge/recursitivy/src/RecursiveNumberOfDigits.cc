#include <iostream>

/**
Statement:
Write a recursive function

     int number_of_digits(int n);
that returns the number of digits of n.

Precondition

We have n ≥ 0.

Observation You only need to submit the required procedure; your main program will be ignored.


*/

using namespace std;

int number_of_digits(int n) {
	if (n < 10) return 1;
	return number_of_digits(n/10) + 1;
}

int main() {
	int x; cin >> x; cout << number_of_digits(x) << endl;
	return 0;
}


