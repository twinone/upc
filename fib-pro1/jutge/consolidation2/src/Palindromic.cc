#include <iostream>

/**
Statement:
Write a function

     bool is_palindromic(int n);
that tells whether the natural number n is a palindromic number or not.

Precondition

n is a natural number.

Observation You only need to submit the required procedure; your main program will be ignored.


*/
using namespace std;

int reverse(int n) {
	int res = 0;
	while (n > 0) {
		res = res * 10 + n%10;
		n /= 10;
	}
	return res;
}
bool is_palindromic(int n) {
	return n == reverse(n);
}


int main() {
	return 0;
}


