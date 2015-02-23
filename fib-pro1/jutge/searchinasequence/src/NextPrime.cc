#include <iostream>
#include <cmath>

/**
Statement:
Write a program that reads a sequence of prime numbers and, for each one, prints the next prime number.

Input

Input is all natural numbers, and consists of a sequence of prime numbers ended with a non-prime number.

Output

For every given prime number, print in a line the next prime number.
*/

using namespace std;


bool is_prime(int n) {
	if (n <= 1) return false;
	int lim = sqrt(n);
	if (n > 1 && n <= 3) return true;
	if(n>2 && n%2 == 0) return false;
	// at this point all factors MUST be odd
	for (int i = 3; i <= lim; i+=2) {
		if (n%i == 0) return false;
	}
	return true;
}

int next_prime(int prime) {
	while (!is_prime(++prime));
	return prime;
}

int main() {

	int x;
	while (cin >> x && is_prime(x)) {
		cout << next_prime(x) << endl;
	}

	return 0;
}


