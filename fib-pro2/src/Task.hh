#ifndef __TASK__
#define __TASK__

#include <set>
#include <string>
#include "Clock.hh"

using namespace std;

// Task may not depend on Comanda.hh
class Task {
private:
	string title;
	set<string> tags;

public:
	/** @brief Default constructor for a Task
	Pre: what is the title of the task, when is the date and time of the task
	Post: The task is created
	*/
	Task(string title);

	// Pre:
	// Post: The title of this task becomes the value of the parameter title
	void set_title(string title);

	// Returns the title of this task
	string get_title();

	// Pre:
	// Post: true if tag was added, false if it was already present
	bool add_tag(string tag);

	// Pre:
	// Post: true if tag was removed, false if not present
	bool delete_tag(string tag);

	// Pre:
	// Post: true if this task contains the tag
	bool has_tag(string tag);

};


#endif