#include <iostream>

/**
Statement:
Use recursion in order to write a program that prints every given number in binary, octal and hexadecimal notation.

Input

Input consists of several natural numbers.

Output

For every given number, print its binary, octal and hexadecimal notation. Follow the format of the example.


*/

using namespace std;

void print_binary(int n) {
	if (n >= 2) print_binary(n/2);
	cout << n%2;
}

void print_octal(int n) {
	if (n >= 8) print_octal(n/8);
	cout << n%8;
}

void print_hex(int n) {
	if (n >= 16) print_hex(n/16);
	if (n%16 >= 10) cout << char('A'-10+(n%16));
	else cout << n%16;
}


int main() {
	int n;
	while (cin >> n) {
		cout << n << " = ";
		print_binary(n); cout << ", ";
		print_octal(n); cout << ", ";
		print_hex(n); cout << endl;
	}
	return 0;
}


