/** @file TaskMan.hh
    @brief TaskMan class
 */

#ifndef __TASKMAN__
#define __TASKMAN__

#include <map>
#include "Clock.hh"
#include "Task.hh"
#include "Filter.hh"
#include "comanda.hh"


typedef map<Clock, Task> Agenda;
typedef vector<Agenda::iterator> Menu;

/** 
class TaskMan
@brief TaskMan is responsible for managing all tasks in the agenda

It will take all processed input from Comanda, and take the
appropriate actions

@author Twinone (Luuk Willemsen)
@author Arnau Badia

*/
class TaskMan {
private:

	/** @brief The current command */
	Comanda command;

	/** @brief Chronologically orderd list of Tasks
	
	Tasks are mapped by a Clock, which is unique  - no two clocks can have the
	same date and time - in the whole Agenda.
	*/
	Agenda agenda;

	/** @brief Ordered Task list, generated after a valid query

	Each Task in the Menu can be accessed through it's position: [0,menu.size())
	*/
	Menu menu;

	/** @brief The current internal time 
	
	May only be modified forward
	*/
	Clock now;

	/** @brief The filter used to filter tags */
	Filter filter;
	
	/** @brief Sets the clock to the specified date/time by Comanda 
	@pre true
	@post If the new time/date was in the future, the now clock will
	contain that time/date
	*/
	void edit_clock();

	/** @brief Populates the Menu with the Tasks that match the query

	This method clears the menu, rebuilds it, filters it and prints it
	@pre true
	@post The Menu matching the query is saved and printed
	*/
	void query_tasks();

	/** @brief Create the menu based on the specified interval

	Possible intervals:
	[beginning of time, now) (past)
	[now, end of time) (future)
	[a 00:00, a 23:59] (user: everything on a given day)
	[a 00:00, b 23:59] (user: everything between two days)
	@pre true
	@post Menu contains all Tasks in the given interval<br>
	@return true if filter_menu() needs to be called
	*/
	bool build_menu();

	/** @brief Filter unmatched Tasks in Menu

	If there's a boolean-expression-filter in the command,
	this method removes all Tasks from the Menu that don't match it
	If there's no expression this method does nothing.
	@pre a Menu is built using build_menu()<br>

	@post The Menu is ready to print
	*/
	void filter_menu();
	
	/** @brief Adds all Tasks between begin and end Clocks to the Menu
	@param closed Whether or not to include the end clock in the interval
	@pre true
	@post Menu contains all Tasks in the interval
	*/
	void add_interval_to_menu(Clock begin, Clock end, bool closed);

	/** @brief Handles task insertion
	@pre true
	@post
	if the Clock is in the future and there is no Task at the same Clock
	the Task is inserted into the Agenda<br>
	Otherwise an error message is printed
	*/
	void insert_task();

	/** @brief Handles task edition
	
	Task editions are done by index. The index of a Task is it's position 
	according to the previously created Menu minus one (Comanda uses [1-n]
	interval, we use [0,n)).<br>
	
	@pre true
	@post The Task is edited or an error message is printed

	@warning An error message will be shown if:
	<ul>
	<li>The Task is already deleted</li>
	<li>The Task is in the past</li>
	<li>The Task's new Clock is in the past</li>
	<li>The Task's new Clock is already in the Agenda</li>
	</ul>
	*/
	void edit_task();

	/** @brief Handles Task removal
	Task removal is done based on their index.
	@pre true
	@post
	The Task is deleted or an error message is printed

	@warning An error message will be shown if the Task is part of the past
	@see edit_task()
	*/
	void delete_task();

	/** @brief Adds Comanda's information to a base Clock
	@pre true
	@post
	The returned clock is the clock in the command
	@param base Retrieve missing values from Comanda from this Clock
	@return the target Clock
	*/
	Clock target_clock(Clock base);

	/** @brief Prints the Menu
	@pre true
	@post The current Menu is printed
	*/
	void print_menu() const;

	/** @brief Checks if a Task can be inserted at a given time
	@pre true
	@post 
	@param clock the Clock to test for insertion
	@return whether the task can be inserted 
	*/
	bool is_valid_target(const Clock& clock) const;

	/** @brief Check if the selected Task can be edited
	@pre true
	@post
	@warning An error message will be shown if:
	<ul>
	<li>Task index out of bounds</li>
	<li>Task is in the past</li>
	<li>Task is already deleted</li>
	</ul>

	@return The menu index or -1 if the task cannot be edited for
	one of the reasons above
	*/
	int can_edit();

	/** @brief Add all tags to a Task
	
	This adds all tags in the command to the given Task.
	@pre true
	@post task contains all tags in the command
	*/
	void add_tags(Task& task);


public:
	/** @brief Empty constructor
	@pre true
	@post Debugging is initially disabled
	*/
	TaskMan();

	/** @brief Starts the taskmanager
	@pre true
	@post The user entered the exit command
	*/
	void run();

	/** @brief Enables debugging
	@pre true
	@post Debugging is enabled on this TaskMan
	*/
	void debug();
};

#endif
