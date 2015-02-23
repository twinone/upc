#include <iostream>
#include <cmath>

/**
Statement:
A natural number n > 0 is called powerful if, for each prime divisor p of n, p2 is also divisor of n. For example, 55125 = 3·3·5·5·5·7·7 is a powerful number, because every prime factor appears, at least, twice.

Your task is to write a program that reads a sequence of numbers m and, for each one, prints all the powerful numbers between 1 and m.

Input

The input is a sequence of natural numbers m > 0.

Output

For each m of the input, print a line with all the powerful numbers between 1 and m, separated by commas and in increasing order.

Observation

Your program must implement and use the function

     bool is_powerful(int n);
that, given an integer strictly positive |n|, indicates if is powerful or is not


*/
using namespace std;

// prints all prime factors in ascending order of n
// Pre: n > 0
bool is_powerful(int n) {
	int fac = 2;
	int count = 0;
	while (n > 1) {
		if (n % fac == 0) {
			n /= fac;
			count++;
		}
		else {
			if (count > 0 && count < 2) { return false; }
			count = 0;
			fac++;
		}
	}
	if (count > 0 && count < 2) return false;
	return true;
}

int main() {

	int x;
	while (cin >> x) {
		bool comma = false;
		for (int i = 1; i <= x; i++) {
			if (is_powerful(i)) {
				if (comma) cout << ",";
				else comma = true;
				cout << i;
			}
		}
		cout << endl;
	}

	return 0;
}


