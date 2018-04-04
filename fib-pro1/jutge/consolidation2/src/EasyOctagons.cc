#include <iostream>

/**
Statement:
Write a program that for every given n prints an “octagon of size n” according to the pattern shown in the examples.

Input

Input consists in several natural numbers n ≥ 2.

Output

For every n, print an “octagon of size n” using capital exes. Do not print any space to the right of the exes. Print an empty line after each octagon.


*/

using namespace std;

// Prints a character c n times.
void print(int g, int x) {
	for (int i = 0; i < g; i++)
		cout << ' ';
	for (int i = 0; i < x; i++)
		cout << 'X';
	cout << endl;
}

// prints an octagon of size s
void print_octagon(int s) {
	int c = s;
	int g = s - 1;
	while (g > 0) {
		print(g, c);
		c += 2;
		g--;
	}
	for (int i = 0; i < s; i++) {
		print(0, c);
	}
	while (c > s) {
		g++;
		c -= 2;
		print(g, c);
	}
	cout << endl;
}


int main() {
	int s;
	while (cin >> s) print_octagon(s);
	return 0;
}


