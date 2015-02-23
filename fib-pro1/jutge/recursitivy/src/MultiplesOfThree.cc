#include <iostream>

/**
Statement:
A well-kown mathematical property states that a natural number is a multiple of three if and only if the sum of its digits is also a multiple of three. For instance, the sum of the digits of 8472 is 8 + 4 + 7 + 2 = 21, which is a multiple of three. Therefore, 8472 is also a multiple of three.

Implement a recursive function

     bool is_multiple_3(int n);
that tells if a strictly positive natural number n is a multiple of three or not.

Solve this problem using a recursive function

     int sum_of_digits(int n);
to return the sum of the digits of a natural number n.

Observation

Here, you are allowed to use the operations of division and integer remainder only with the number 10. Otherwise, this exercise would be totally trivial!
*/

using namespace std;


int sum_of_digits(int n) {
	if (n < 10) return n;
	return n%10 + sum_of_digits(n/10);
}

bool is_multiple_3(int n) {
	while (n > 10) {
		n = sum_of_digits(n);
	}
	return n == 0 or n == 3 or n == 6 or n == 9;
}



int main() {
	int n;
	while (cin >> n) {
		if (is_multiple_3(n)) cout << "true" << endl;
		else cout << "false" << endl;
	}
	return 0;
}


