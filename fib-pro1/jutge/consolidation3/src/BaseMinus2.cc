#include <iostream>

/**
Statement:
Write a program to print numbers in base -2.

Input

Input consists of several integer numbers, each with at most nine digits.

Output

For every given number, print it in base -2 following the format of the example.


*/

using namespace std;

void print_binary(int n) {
	if (n >= (-2)) print_binary(n/(-2));
	cout << n%(-2);
}
int main() {
	int n;
	while (cin >> n) {
		cout << n << ": ";
		print_binary(n);
		cout << endl;
	}
	return 0;
}


