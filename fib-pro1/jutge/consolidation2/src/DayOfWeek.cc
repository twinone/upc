#include <iostream>

/**
Statement:
Write a function

     string day_of_the_week(int d, int m, int y);
that, given a valid date with day d, month m and year y, returns its day of the week, that is, “Monday”, or “Tuesday”, …

To compute it, use the congruence of Zeller. Let d be the day, m be the month, and y be the year. Then,

Subtract two from the month m, and if the result is zero or less, add 12 to the month and subtract one from the year. Call m′ the new month and call y′ the new year.
Compute the century c (the first two digits of the year) from the year y′.
Compute the year a inside the century (the two last digits of the year) from the year y′.
Compute
        f = ⌊ 2.6m′ − 0.2 ⌋ + d + a + ⌊ a/4 ⌋ + ⌊ c/4 ⌋ − 2c.
Finally, f modulo 7 gives us the desired result, taking into account that 0 represents Sunday, 1 represents Monday, 2 represents Tuesday, …, and 6 represents Saturday.
Precondition The parameter y is between 1800 and 9999, both included. The date is valid.

Hint

Watch out for modulos of negative numbers!

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;
int abs(int a) {
	if (a >= 0) return a;
	return -a;
}
string dow(int d) {
	if (d == 0) return "Sunday";
	if (d == 1) return "Monday";
	if (d == 2) return "Tuesday";
	if (d == 3) return "Wednesday";
	if (d == 4) return "Thursday";
	if (d == 5) return "Friday";
	return "Saturday";
}

string day_of_the_week(int d, int m, int y) {
	m -= 2;
	if (m <= 0) { m += 12; y--; }
	int a = y % 100;
	int c = (y - a) / 100;
	// cout << "a: " << a << " c: " << c << endl;
	int f = abs(2.6*m - 0.2) + d + a + abs(a/4) + abs(c/4) - 2*c;
	f%=7;
	if (f < 0) f += 7;
	// cout << "f: " << f << endl;
	return dow(f);
}


int main() {
	int d,m,y; cin >> d >> m >> y;
	cout << day_of_the_week(d,m,y) << endl;
	return 0;
}


