#include <iostream>
#include <vector>
#include <string>

/**
Statement:
An ISBN code (International Standard Book Number) is a code of ten digits that identifies books. In fact, the first nine digits represent the book, and the last digit is used to check that the ISBN code is correct. To validate an ISBN code, we must add up ten times the first digit, plus nine times the second, ..., plus once the last digit. If the sum is divisible by eleven, the ISBN code is regarded as valid.

For instance, 0201103311 is a valid ISBN code, because

    10*0 + 9*2 + 8*0 + 7*1 + 6*1 + 5*0 + 4*3 + 3*3 + 2*1 + 1*1 = 55 = 5*11.
Each of the first nine digits is a value between 0 and 9. Sometimes the last number must be 10; this is done by writing an X. For instance, 156881111X.

Write a program that computes the complet ISBN code of codes with a missing digit.

Input

Input is a sequence of valid ISBN codes but with an unknown digit marked with ‘?’.

Output For each code of the input, print in a line the unknown digit.

Observation

This problem is from “The British Informatics Olympiad for schools and colleges”.

*/

using namespace std;


int main() {
	string isbn;
	while (cin >> isbn) {
		int fac = -1;
		int s = 0;
		for (int i = 10; i >= 1; --i) {
			char c = isbn[10-i];
			if (c != '?') {
				if (c == 'X') s += 10;
				else s += i * (c - '0');
				// cout << "char: " << c << endl;
				// cout << "partial sum["<<i<<"]: " << s << endl;;
			}
			else fac = i;
		}
		// cout << "?fac: " << fac << endl;
		for (int i = 0; i < 11; ++i) {
			if ((s + i*fac) % 11 == 0) {
				if (i <= 9) cout << i << endl;
				else cout << 'X' << endl;
			}
		}
	}


	return 0;
}


