#ifndef __DATETIME__
#define __DATETIME__

#include <string>

using namespace std;


class Clock {

private:
	int year, month, day;
	int hour, minute;

public:
	Clock();

	void set_date(string date);
	void set_time(string time);
	// Returns a human readable representation of this object
	string to_string() const;
	// Returns the time of this clock
	string time() const;
	// Returns the date of this clock
	string date() const;

	bool is_future(const Clock& c);
	bool operator<(Clock const& rhv) const;	
	bool operator==(Clock const& rhv) const;
};

#endif