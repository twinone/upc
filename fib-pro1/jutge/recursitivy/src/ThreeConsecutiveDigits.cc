#include <iostream>

/**
Statement:
Write a recursive function

     bool three_equal_consecutive_digits(int n, int b);
that returns true if and only if the natural number n has three or more equal consecutive digits when expressed in base b.

For example, the number 44344 does not have three equal consecutive digits in base 10. By contrast, 159 in ternary is 12220, so it does have three equal consecutive digits in base 3.

Precondition

It holds 0 ≤ n ≤ 109 and 2 ≤ b ≤ 100.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;

bool three_equal_consecutive_digits(int n, int b) {
	// Check n >= 3 digits
	if (n < b * b) return false;
	int d1 = n%b;
	int d2 = (n/b)%b;
	int d3 = (n/b/b)%b;
	// cout << "digits: " << d1 << " " << d2 << " " << d3 << endl;
	if (d1 == d2 and d2 == d3) return true;
	// Try from next digit
	return three_equal_consecutive_digits(n/b, b);	
}


int main() {
	int n, b; cin >> n >> b;
	cout << three_equal_consecutive_digits(n, b) << endl;
	return 0;
}


