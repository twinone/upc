#ifndef __TASKMAN__
#define __TASKMAN__

#include "Clock.hh"
#include "comanda.hh"

// Printed when:
// 1) The clock is changed to the future
#define NOT_PERFORMED "No s’ha realitzat."

class TaskMan {
private:
	// The current command
	Comanda comanda;

	// The current time
	Clock now;
	
	// Operations with the current command

	void do_insert();
	void do_query();
	void do_delete();

public:
	TaskMan();

	/** @brief Starts the taskmanager
	Pre: 
	Post: The user entered the exit command
	*/
	void run();
};

#endif /** __TASKMAN__ */
