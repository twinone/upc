#include <iostream>

/**
Statement:
Write a procedure

     void decompose(int n, int& h, int& m, int& s);
that, given a quantity of seconds n, computes how many hours h, minutes m and seconds s it represents. That is, we must have s + 60m + 3600h = n, with 0≤ s <60 and 0≤ m <60.

Precondition

n is a natural number.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;

void decompose(int n, int& h, int& m, int& s) {
	h = n / 3600;
	m = (n % 3600) / 60;
	s = (n % 60);
}

int main() {
	return 0;
}


