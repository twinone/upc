#include <iostream>

/**
Statement:
Given a natural number n, let s(n) be the sum of the digits of n. In this exercise, we say that n is a perfect prime if the infinite sequence n, s(n), s(s(n)), …only contains prime numbers. For instance, 977 is a perfect prime, because 977, 9 + 7 + 7 = 23, 2 + 3 = 5, 5, …, are all prime numbers.

Write a recursive function

     bool is_perfect_prime(int n);
that tells if a natural number n is a perfect prime or not.

Precondition

We have n ≥ 0.

Observation You only need to submit the required procedure; your main program will be ignored.


*/

using namespace std;

int sum_of_digits(int n) {
	if (n < 10) return n;
	return n%10 + sum_of_digits(n/10);
}

bool is_prime(int n) {
	if (n <= 1) return false;
	for (int i = 2; i*i <= n; i++) {
		if (n%i == 0) return false;
	}
	return true;
}

bool is_perfect_prime(int n) {
	if (n < 10) return is_prime(n);
	return is_prime(n) and is_perfect_prime(sum_of_digits(n));
}


int main() {
	int n; cin >> n;
	cout << sum_of_digits(n) << endl;
	cout << is_perfect_prime(n) << endl;
	return 0;
}


