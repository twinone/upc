#include <iostream>

/**
Statement:
Write a function

     int max4(int a, int b, int c, int d);
that returns the maximum of four given integer numbers a, b, c and d.

Observation You only need to submit the required procedure; your main program will be ignored.

Hint

Using the function max2(a, b) of the exercise P57846: “Maximum of two integer numbers” could be useful.


*/

using namespace std;

int max4(int a, int b, int c, int d) {
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	if (d > max) max = d;
	return max;
}

int main() {
	return 0;
}


