#include <iostream>

/**
Statement:
Write an iterative function

     int number_of_digits(int n);
that returns the number of digits of n.

Precondition

We have n ≥ 0.

Observation You only need to submit the required procedure; your main program will be ignored
*/

using namespace std;


int number_of_digits(int n) {
	int t = 1;
	while ((n /= 10) > 0) {
		t++;
	}
	return t;
}



int main() {
	int x;
	cin >>x;
	cout << number_of_digits(x) << endl;
	return 0;
}


