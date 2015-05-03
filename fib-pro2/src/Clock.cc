#include "Clock.hh"
#include <sstream>
#include <iostream>

Clock::Clock() { to_origin(); }

Clock::Clock(string date, string time) { set_date(date); set_time(time); }

void Clock::set_date(string date) {
	bot = eot = false;
	day   = 10 * int(date[0]-'0') + int(date[1]-'0');
	month = 10 * int(date[3]-'0') + int(date[4]-'0');
	year  = 10 * int(date[6]-'0') + int(date[7]-'0');
}

void Clock::set_time(string time) {
	bot = eot = false;
	hour = 10 * int(time[0]-'0') + int(time[1]-'0');
	minute   = 10 * int(time[3]-'0') + int(time[4]-'0');
}

string Clock::to_string() const {
	// for debugging
	if (eot) return "end_of_time";
	if (bot) return "beginning_of_time";
	return date() + " " + time();
}

string Clock::time() const {
	string s;
	s += char((hour / 10) +'0');
	s += char((hour % 10) +'0');
	s += ':';
	s += char((minute / 10) +'0');
	s += char((minute % 10) +'0');
	return s;
}

string Clock::date() const {
	string s;
	s += char((day / 10) +'0');
	s += char((day % 10) +'0');
	s += '.';
	s += char((month / 10) +'0');
	s += char((month % 10) +'0');
	s += '.';
	s += char((year / 10) +'0');
	s += char((year % 10) +'0');
	return s;
}

bool Clock::operator<(Clock const& c) const {
	if (bot and not c.bot) return true;
	if (eot and not c.eot) return false;
	if (year != c.year) return year < c.year;
	if (month != c.month) return month < c.month;
	if (day != c.day) return day < c.day;
	if (hour != c.hour) return hour < c.hour;
	return minute < c.minute;
}

bool Clock::operator==(Clock const& c) const {
	if (eot and c.eot or bot and c.bot) return true;
	return year == c.year
	and	month == c.month
	and	day == c.day
	and	hour == c.hour
	and	minute == c.minute;
}
bool Clock::operator<=(Clock const& c) const { return c < *this or c == *this; }



void Clock::to_origin() {
	year = 15;
	month = 04;
	day = 20;
	hour = minute = 00;
}

void Clock::to_bot() {
	eot = false; bot = true;
}

void Clock::to_eot() {
	eot = true; bot = false;
}
