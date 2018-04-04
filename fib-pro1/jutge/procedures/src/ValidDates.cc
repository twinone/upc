#include <iostream>

/**
Statement:

*/

using namespace std;


bool is_leap_year(int year) {
	// Copied from introduction
	bool leap = year % 4 == 0;
	if (year % 100 == 0) leap = false;
	if (year % 400 == 0) leap = true;
	return leap;
}


// Why would you do it d-m-y instead of y-m-d?
bool is_valid_date(int d, int m, int y) {
	if (d <= 0 || d>31 || m <= 0 || m>12 || y < 1800 || y > 9999) return false;
	int maxDays;
	switch(m) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		maxDays = 31;
		break;
		case 2:
		maxDays = is_leap_year(y) ? 29 : 28;
		break;
		default:
		maxDays = 30;
		break;
	}
	if (d > maxDays) return false;
	return true;
}



int main() {
	return 0;
}


