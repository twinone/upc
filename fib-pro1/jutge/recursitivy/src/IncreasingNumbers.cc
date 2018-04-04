#include <iostream>

/**
Statement:
In this exercise, we say that a natural number is increasing if every digit is less than or equal to the digit which is on its right (if any).

Write a recursive function

     bool is_increasing(int n);
that tells if a natural number n is increasing or not.

Observation You only need to submit the required procedure; your main program will be ignored.


*/

using namespace std;

bool is_increasing(int n) {
	if (n < 10) return true;
	return n%10 >= (n/10)%10 and is_increasing(n/10);
}



int main() {
	return 0;
}


