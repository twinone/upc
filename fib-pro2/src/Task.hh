#ifndef __TASK__
#define __TASK__

// Task may not depend on Comanda.hh
class Task {
private:
	// Title of the task
	string what;
	// Date and time of the task
	Clock when;
	// TODO: determine best type of container
	// TODO: save tags with or without "#"? -> consider search efficiency
	??container??<String> tags

public:
	/** @brief Default constructor for a Task
	Pre: what is the title of the task, when is the date and time of the task
	Post: The task is created
	*/
	Task(string what, Clock when);
	// TODO: Ask if we can use a vector in parameters
	// Task(string title, Clock time, vector<string> tags);

};


#endif