#include <iostream>
#include <algorithm> // For reverse
#include <sstream> // For string streams


/**
Statement:
Write a program that reads a number and prints its hexadecimal representation reversed. Follow the convention to use the letters from ‘A’ to ‘F’ to represent the values from 10 to 15.

Input

Input consists of a natural number.

Output

Print, reversed, the hexadecimal representation of the number, with as many zeros at its left as required.
*/

using namespace std;

// Recursively obtain the hex representation of a decimal number (int)

int main() {


	long s;
	cin >> s;

	stringstream sstream;
	sstream << hex << s;
	string result = sstream.str();


	reverse(result.begin(), result.end());
	transform(result.begin(), result.end(),result.begin(), ::toupper);

	cout << result << endl;
	return 0;
}
