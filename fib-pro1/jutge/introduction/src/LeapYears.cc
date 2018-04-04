#include <iostream>

/**
Statement:
Write a program that tells if a year is or is not a leap year.

A leap year has 366 days. After the Gregorian reform, the leap years are those multiple of four that do not end with two zeros, and also the years ending with two zeros such that, after removing these two zeros, are divisible by four. Thus, 1800 and 1900, although being multiples of four, were not leap years; by contrast, 2000 was a leap year.

Input

Input consists of a natural number between 1800 and 9999.

Output

If the year is a leap year, print “YES”; otherwise print “NO”.
*/

using namespace std;

int main() {
	int year;
	cin >> year;

	bool leap = year % 4 == 0;
	if (year % 100 == 0) leap = false;
	if (year % 400 == 0) leap = true;

	cout << (leap ? "YES" : "NO") << endl;

	return 0;
}


