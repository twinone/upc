/** @file Task.hh
    @brief Task class
 */

#ifndef __TASK__
#define __TASK__

#include <set>
#include <string>
#include "Clock.hh"



/** 
class Task
@brief A Task is a to-do event to be used as part or a Agenda.

Tasks consist of a mandatory title and optional tags. Tags always
start with a #. This class allows you to manage the title and tags
efficiently.

@author Twinone (Luuk Willemsen)
@author Arnau Badia
*/
class Task {
private:
	string title;
	set<string> tags;

public:

	/** @brief Empty constructor for a Task
	@pre true
	@post The Task is initialized with no title
	*/
	Task();

	/** @brief Default constructor for a Task
	@pre title != NULL
	@post The title of the task is title
	@see set_title()
	*/
	Task(string title);

	/** @brief Title setter
	@pre title != NULL
	@post the title of this task is title
	*/
	void set_title(string title);

	/** @brief Title getter
	@pre true
	@post the title of this task is title
	*/
	string get_title();

	/** @brief Adds a tag to this Task
	@pre true
	@post
	@return true if tag was added, false if it was already present
	*/
	bool add_tag(string tag);

	/** @brief Adds a tag to this Task
	@pre true
	@post
	@return true if tag was removed, false if not present
	*/
	bool delete_tag(string tag);

	/** @brief check if this Task has a given tag
	@pre true
	@post
	@return true if this task contains the tag
	*/
	bool has_tag(string tag);

	/** @brief print all tags in chronological order
	@pre true
	@post tags are printed
	@param delim The delimiter to be used between tags
	*/
	void print_tags(string delim);

};


#endif