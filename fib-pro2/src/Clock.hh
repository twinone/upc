/** @file Clock.hh
    @brief Clock class
 */

#ifndef __DATETIME__
#define __DATETIME__

#include <string>

using namespace std;

/** 
class Clock
@brief Clock is is a representation of a date and time

@author Twinone (Luuk Willemsen)
@author Arnau Badia

*/
class Clock {

private:
	int year, month, day;
	int hour, minute;

	/** @brief The beginning of time, no time is smaller than this */
	bool bot;

	/** @brief The end of time, no time is bigger than this */
	bool eot;

public:
	/** @brief Empty constructor
	@pre true
	@post This clock is initialized to the origin
	@see to_origin()
	*/
	Clock();

	/** @brief Initialize this Clock with a date and a time
	
	@pre true
	@post This Clock's date and time will be date and time
	@see set_date()
	@see set_time()
	*/
	Clock(string date, string time);

	/** @brief Set the clock to the specified date
	@pre true
	@post The clock's date is date
	*/
	void set_date(string date);

	/** @brief Set the clock to the specified time
	@pre true
	@post The clock's time is time
	*/
	void set_time(string time);

	/** @brief Get the time and date of this Clock
	@pre true
	@post 
	@return a human-readable representation of this object
	*/
	string to_string() const;

	/** @brief Get the time of this Clock
	@pre true
	@post 
	@return a human-readable representation of this object
	*/	
	string time() const;

	/** @brief Get the date of this Clock
	@pre true
	@post 
	@return a human-readable representation of this object
	*/
	string date() const;

	/** @brief Set the clock to the beginning of time
	@pre true
	@post All clocks you compare with this will always be strictly bigger
	*/
	void to_bot();
	/** @brief Set the clock to the end of time
	@pre true
	@post All clocks you compare with this will always be strictly smaller
	*/
	void to_eot();

	/** @brief Set the Clock to the origin
	@pre true
	@post This Clock will be at 20.04.15 00:00
	*/
	void to_origin();

	bool operator<(Clock const& rhv) const;	
	bool operator==(Clock const& rhv) const;
	bool operator<=(Clock const& rhv) const;
};

#endif