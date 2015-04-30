#include "Clock.hh"
#include <sstream>
#include <iostream>


// Ugly function to pad an int with a leading zero if needed
string pad2(int n) {
	stringstream ss;
	if (n < 10) {
		ss << 0;
	}
	ss << n;
	return ss.str();
}

Clock::Clock() {
	year = 15;
	month = 04;
	day = 20;
	hour = minute = 00;
}

void Clock::set_date(string date) {
	char c;
	stringstream ss(date);
	ss >> day >> c >> month >> c >> year;
}

void Clock::set_time(string time) {
	char c;
	stringstream ss(time);
	ss >> hour >> c >> minute;
}

string Clock::to_string() const {
	return date() + " " + time();
}

string Clock::time() const {
	stringstream ss;
	ss << pad2(hour) << ":" << pad2(minute);
	return ss.str();
}

string Clock::date() const {
	stringstream ss;
	ss << pad2(day) << "." << pad2(month) << "." << pad2(year);
	return ss.str();
}

bool Clock::operator<(Clock const& c) const {
	if (year != c.year) return year < c.year;
	if (month != c.month) return month < c.month;
	if (day != c.day) return day < c.day;
	if (hour != c.hour) return hour < c.hour;
	return minute < c.minute;
}

bool Clock::operator==(Clock const& c) const {
	return year == c.year
	and	month == c.month
	and	day == c.day
	and	hour == c.hour
	and	minute == c.minute;
}
