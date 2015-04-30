#ifndef __TASKMAN__
#define __TASKMAN__

class TaskMan {
private:
	Comanda comanda;
	
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
