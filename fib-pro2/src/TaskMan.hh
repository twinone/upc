#ifndef __TASKMAN__
#define __TASKMAN__

#include <map>
#include "Clock.hh"
#include "Task.hh"
#include "comanda.hh"

// Printed when:
// 1) The clock is changed to the future
#define NOT_PERFORMED "No s’ha realitzat."

typedef map<Clock, Task> Calendar;

class TaskMan {
private:
	// True if debugging messages should be shown
	bool DEBUG;
	
	// The current command
	Comanda command;

	Calendar calendar;

	vector<Calendar::iterator> menu;

	// The current time
	Clock now;
	
	void process_clock();
	void process_task();

	// Build the menu
	void build_menu();
	// Filter menu by tags
	void filter_menu();
	
	// Adds an interval of time to the menu
	// The left part is always closed
	// The right part is closed if closed == true
	void add_interval_to_menu(Clock begin, Clock end, bool closed);
	void insert_task();
	void edit_task();
	void delete_task();

	// Returns a Clock based on the target in the current Command,
	// filling in missing info with the "base" Clock
	// Cannot be const because comanda implementation doesn't use const
	Clock target_clock(Clock base);
	// Returns a clock at the beginning of time
	Clock beginning_of_time() const;
	void print_menu() const;
	// Returns true if the clock is in the future and there is no 
	// task already in the calendar with the same clock
	bool can_insert(const Clock& c) const;
	
	// Cannot be const because comanda implementation doesn't use const
	void add_tags(Task& t);


public:
	TaskMan();

	/** @brief Starts the taskmanager
	Pre: 
	Post: The user entered the exit command
	*/
	void run();
	/** Enables debugging */
	void debug();
};

#endif /** __TASKMAN__ */
