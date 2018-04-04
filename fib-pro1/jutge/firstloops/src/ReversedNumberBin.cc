#include <iostream>
#include <algorithm> // For reverse
/**
Statement:
Write a program that reads a number and prints its binary representation reversed.

Input

Input consists of a natural number.

Output

Print, reversed, the binary representation of the number, with as many zeros at its left as required.*/

using namespace std;

// Recursively obtain the binary representation of a decimal number (int)
string DecToBin(long number) {
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";
    return DecToBin(number / 2) + (number % 2 == 0 ? "0" : "1");
}

int main() {
	long s;
	cin >> s;

	string bin = DecToBin(s);

	reverse(bin.begin(), bin.end());
	cout << bin << endl;
	return 0;
}


