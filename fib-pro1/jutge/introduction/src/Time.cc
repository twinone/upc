#include <iostream>

/**
Statement:
Write a program that, given a number of seconds n, prints the number of hours, minutes and seconds represented by n.

Input

Input consists of a natural number n.

Output

Print three natural numbers h, m, s such that 3600h+60m+s=n, with m<60 and s<60.
*/

using namespace std;

int main() {
	long n;
	cin >> n;

	long h = n / 3600;
	int m = (n % 3600) / 60;
	int s = (n % 60);

	cout << h << " " << m << " " << s << endl;

	return 0;
}


