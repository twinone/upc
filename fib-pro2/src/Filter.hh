#ifndef __FILTER__
#define __FILTER__

#include "Task.hh"

class Filter {
private:
	/** @brief Current token pointer */
	int ctp;
	
	/** @brief Current filter */
	string filter;

	Task task;

	bool eval();
	bool eval_quick();
	bool eval_tag();

	void orskip();
	void andskip();

	string read_tag();

	// for debugging only, prints the filter
	// and the position of ctp below it
	// oh, and it also prints a cool message
	void dbg_print_pos(string msg);

public:

	/** @brief Default constructor
	@pre true
	@post
	*/
	Filter();

	/** @brief Set the filter string
	@pre true
	@post filter will be used to match() against
	*/
	void set_filter(const string& filter);

	/** @brief Check if the filter matches the task
	@pre set_filter() is called with the filter string
	@post
	@return whether the Task matches the filter
	*/
	bool match(const Task& t);


};
#endif