#include <iostream>
#include <algorithm> // For reverse
/**
Statement:
Write a program that reads a number and prints it reversed.

Input

Input consists of a natural number.

Output

Print the number reversed, with as many zeros at its left as it has at its right.
*/

using namespace std;

int main() {
	string s;
	cin >> s;

	reverse(s.begin(), s.end());
	cout << s << endl;
	return 0;
}


