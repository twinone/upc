#include <iostream>
#include <vector>
#include <cmath>
/**
Statement:
Write a program that reads sequences of natural numbers, and for each one tells if it has two elements such that their sum is a prime number.

Input

Input consists of several sequences, each one in a line. Each sequence consists of a natural number n, followed by n natural numbers x1, …, xn.

Output

For each input sequence, print “yes” or “no” depending on if it is possible to find two elements xi and xj (with i ≠ j) such that xi + xj is a prime number.

Observation

Using arrays, it is possible to precompute which numbers are prime and which are not up to a certain maximum. In this exercice it is not possible because we do not know any maximum, and it is not necessary for efficiency reasons because all the numbers are small enough.


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

bool has_prime_pair(vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i; j < v.size(); ++j) {
			if (i != j and is_prime(v[i]+v[j])) {
			// cout << "found pair: " << v[i] << " + " << v[j] << endl;
			return true;
			}
		}
	}
	return false;
}
int main() {
	int n;
	while(cin >> n) {
		vector<int> v(n);
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}
		cout << (has_prime_pair(v) ? "yes" : "no") << endl;

	}

	return 0;
}


