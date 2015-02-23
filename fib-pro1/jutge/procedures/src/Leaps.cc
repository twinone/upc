#include <iostream>

/**
Statement:
Write a function

     bool is_leap_year(int year);
that tells if the given year is a leap year or not. To recall the rules about leap years, check the exercise P61634: “Leap years”.

Precondition The parameter year is between 1800 and 9999, both included.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;

bool is_leap_year(int year) {
	// Copied from introduction
	bool leap = year % 4 == 0;
	if (year % 100 == 0) leap = false;
	if (year % 400 == 0) leap = true;
	return leap;
}


int main() {
	return 0;
}


