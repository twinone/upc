#include <iostream>

/**
Statement:
Write a program that reads two words and tells their lexicographic order.

Input

Input consists of two words a and b, made up of only lowercase letters.

Output

Print a line telling if a < b, a > b or a = b, following the format of the examples exactly.

Observation

If you use a modern programming language, this exercise should be trivial.
*/

using namespace std;

int main() {

	string a, b;
	cin >> a >> b;

	char symbol;
	symbol = '=';
	if (a < b) {
		symbol = '<';
	} else if (a > b) {
		symbol = '>';
	}

	cout << a << " " << symbol << " " << b << endl;

	return 0;
}


