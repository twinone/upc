#include <iostream>
#include <cmath>

/**
Statement:
Write a program that reads a sequence of natural numbers and, for each one, tells if it is a prime number or not. Remember that a natural number is prime if and only if it is greater than 1 and it does not have any positive divisor other than 1 and itself.

Input

Input consists of a number n, followed by n natural numbers.

Output

For every given natural number, tell in a line if it is prime or not, following the format of the example.

Hint

For every given n, at most about √n  steps are needed to know if it is prime or not.
*/

using namespace std;

bool is_prime(int n) {
	if (n <= 1) return false;
	int lim = sqrt(n);
	for (int i = 2; i <= lim; i++) {
		if (n%i == 0) return false;
	}
	return true;
}
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		if (is_prime(x)) cout << x << " is prime" << endl;
		else			 cout << x << " is not prime" << endl;
	}

	return 0;
}


