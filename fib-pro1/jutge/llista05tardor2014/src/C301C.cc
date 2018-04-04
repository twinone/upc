#include <iostream>
#include <cmath>

/**
Statement:
Given a natural number n ≥ 1, being s(n) the sum of its divisors not counting itself. A number n ≥ 3 is called popiropis if n = s(n−2) + s(n) + s(n+2). A number n ≥ 3 is called k-popiropis if n*k = s(n−2) + s(n) + s(n+2) for an integer k ≥ 2.

For instance, the number 133 is popiropis, because s(131) = 1, s(133) = 27 and s(135) = 105. Besides, 132 is 3-popiropis, because s(130) + s(132) + s(134) = 396 = 132*3.

Your task is to write a program that, for each natural number given, print if it is popiropis, if is k-popiropis (and which is the value of k), or if it is nothing.

Input

The input is a sequence of natural numbers n ≥ 3.

Output

Your program must print a line for each n, indicating which class is: popiropis, k-popiropis, or nothing.

Observation

Your program must implement and use the function

     int sum_divisors(int n);
that, given a natural number |n| different than 0, returns the sum of its divisors (not counting itself).
*/

using namespace std;

int sum_divisors(int n) {
	int sum = 0;
	for (int i = 1; i <= n/2; i++){
		if(n%i == 0) {
			sum += i;
		} 
	}
	return sum;
}

// returns the popiropisness of n or 0 if not popiropis 
int get_popiropisness(int n) {
	int sum = sum_divisors(n-2) + sum_divisors(n) + sum_divisors(n+2);
	return (sum % n == 0) ? (sum / n) : 0;
}

int main() {
	int x;
	while (cin >> x) {
		int popi = get_popiropisness(x);
		cout << x << ": ";
		if (popi == 0) cout << "nothing" << endl;
		else if (popi == 1) cout << "popiropis" << endl;
		else cout << popi << "-popiropis" << endl;
	}

	return 0;
}


