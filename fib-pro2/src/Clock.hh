#ifndef __DATETIME__
#define __DATETIME__

class Clock {

private:
	int m_year, m_month, m_day;
	int m_hour, m_minute;

public:
	void set_date(string date);
	void set_time(string time);
};

#endif