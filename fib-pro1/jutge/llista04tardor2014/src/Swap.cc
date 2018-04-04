#include <iostream>

/**
Statement:
Write a procedure

     void swap2(int& a, int& b);
that swaps the value of its parameters.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;


void swap2(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int main() {
	return 0;
}


