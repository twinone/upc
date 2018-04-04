#include <iostream>

/**
Statement:
In the planet Badenia is used a system of dates different to ours. Although a date is identified
like in our case with a day, a month and a year, we do not know how many months has a
year, nor how many days has a month. However, it should not be an impediment to solve
this problem:
Given a sequence of badenic dates, you must write the first date that it is between its previous
one and its posterior one in the sequence. If there are not any, indicate it.
For instance, 32/15/2007 is between 23/2/1981 and 1/1/10234, because is greater
than the first date and less than the second date. Another instance, 10/10/2 is between
100/10/2 and 100/1/2, because is greater than the first date and less than the second
date.
Using the definition
struct Date {
int day, month, year;
};
your program must include and use the function
bool less than (const Date& d1, const Date& d2);
that returns true if and only if the date d1 is strictly less than date d2.
Input
The input starts with a natural number n ≥ 3. Followed by n different badenic dates, each
one described with three natural numbers separated by a slash, in this oder: day, month and
year
Output
Your program must print the first date that it is between its previous one and its posterior
one in the sequence. If there is not any, it must indicate it. Follow the format of the instance.
*/

using namespace std;

struct Date {
	int day, month, year;
};

bool less_than(const Date& d1, const Date& d2) {
	if (d1.year != d2.year) return d1.year < d2.year;
	if (d1.month != d2.month) return d1.month < d2.month;
	return d1.day < d2.day;
}

Date read() {
	char ign;
	Date d;
	cin >> d.day >> ign >> d.month >> ign >> d.year;
	return d;
}
void print_date(Date& d) {
	cout << d.day << '/' << d.month << '/' << d.year << endl;
}

int main() {
	int n;
	cin >> n;
	Date d0, d1, d2;
	d0 = read(); d1 = read();
	bool solved = false;
	for (int i = 0; i < n-2 and not solved; ++i) {
		d2 = read();
		bool lt01 = less_than(d0, d1);
		bool lt12 = less_than(d1, d2);

		if ((lt01 and lt12) or (not lt01 and not lt12)) {
			print_date(d1);
			solved = true;
		}

		d0 = d1; d1 = d2;
	}
	if (!solved) cout << "no date found" << endl;
	return 0;
}


