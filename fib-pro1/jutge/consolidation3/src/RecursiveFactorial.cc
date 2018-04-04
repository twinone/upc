#include <iostream>

/**
Statement:
Write a function

     int factorial(int n);
that returns n!.

Solve this problem recursively.

Precondition

Assume 0≤ n ≤ 12.

Observation You only need to submit the required procedure; your main program will be ignored.


*/

using namespace std;

int factorial(int n) {
	if (n == 0) return 1;
	if (n <= 2) return n;
	return n * factorial(n-1);
}	



int main() {
	return 0;
}


