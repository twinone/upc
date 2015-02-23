#include <iostream>

/**
Statement:
Write a program that reads a letter and prints it in lowercase if it was uppercase, or prints it in uppercase if it was lowercase.

Input

Input consists of a letter.

Output

Print a line with the given letter in lowercase if it was uppercase, or in uppercase if it was lowercase.
*/

using namespace std;

int main() {
	char a;

	cin >> a;
	// We have to cast to a char because if not toupper and tolower return an int...
	cout << (char)(islower(a) ? toupper(a) : tolower(a)) << endl;
	return 0;
}


