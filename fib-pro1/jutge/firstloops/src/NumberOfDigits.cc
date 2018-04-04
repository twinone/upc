#include <iostream>

/**
Statement:
Write a program that reads a number and prints its number of digits.

Input

Input consists of a natural number n.

Output

Print the number of digits of n.


*/

using namespace std;

int main() {

	string s;
	cin >> s;

	cout << "The number of digits of " << s << " is " << s.size() << "." << endl;

	return 0;
}


