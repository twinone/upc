#include <iostream>

/**
Statement:
Write a function

     int factorial(int n);
that returns n!.

Solve this problem iteratively.

Precondition

Assume 0≤ n ≤ 12.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;

int factorial(int n) {
	int prod = 1;
	while (n >= 2) {
		prod *= n--;
	}
	return prod;
}

int main() {
	return 0;
}


