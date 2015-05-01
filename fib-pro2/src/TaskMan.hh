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

	void query_tasks();
	void insert_task();
	void edit_task();
	void delete_task();

	// Returns a Clock based on the target in the current Command,
	// filling in missing info with the now Clock
	Clock target_clock();
	void print_menu();

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
