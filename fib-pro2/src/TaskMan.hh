#ifndef __TASKMAN__
#define __TASKMAN__

#include <map>
#include "Clock.hh"
#include "Task.hh"
#include "comanda.hh"

// Printed when:
// 1) The clock is changed to the future
#define NOT_PERFORMED "No s’ha realitzat."

typedef map<Clock, Task> Agenda;
typedef map<int, Agenda::iterator> Menu;

class TaskMan {
private:
	// The current command
	Comanda command;

	Agenda agenda;

	Menu menu;

	// The current time
	Clock now;
	
	// Operations with the current command

	void process_clock();
	void process_task();

	void query_task();
	void insert_task();
	void edit_task();
	void delete_task();

	// Returns a clock based on now.
	// If c has a time or a date, those will be used instead of the ones in now
	Clock target_clock();

public:
	TaskMan();

	/** @brief Starts the taskmanager
	Pre: 
	Post: The user entered the exit command
	*/
	void run();
};

#endif /** __TASKMAN__ */
