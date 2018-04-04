#include <iostream>
#include <cmath>
/**
Statement:
Implement an efficient function

     int largest_prime_factor(int n);
that returns the largest prime factor of n.

Precondition

It holds n ≥ 2.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;

int largest_prime_factor(int n) {
	int f = 2;
	while (n > 1 && f * f <= n) {
		while (n%f == 0) {
			n /= f;
		}
		f++;
	}
	if (n != 1) return n;
	return f-1;
}

// Include this function because it's in the examples.
int factor_mes_gran(int n) { return largest_prime_factor(n); }

int main() {
	int x;
	cin >> x;
	cout << largest_prime_factor(x) << endl;
	return 0;
}


