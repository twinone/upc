/** @file Filter.hh
@brief Filter class
 */
#ifndef __FILTER__
#define __FILTER__

#include "Task.hh"

/** 
class Filter
@brief This class evaluates a tagfilter on a Task

A tagfilter is a single tag or a boolean expression of tags that
should be part of the Task.

@author Twinone (Luuk Willemsen)
@author Arnau Badia
*/
class Filter {
private:

	string::const_iterator begin;
	string::const_iterator end;
	/** @brief Current token pointer */
	string::const_iterator ctp;
	
	/** @brief Current Task */
	Task task;

	/** @brief Evaluate an expression completely

	This method evaluates the expression at ctp including ORs and ANDs
	(in contrast to eval_quick())

	We define expression as:
	<ul>
	<li>A tag</li>
	<li>A list of tags separated by "," or "."</li>
	<li>That list or tag wrapped inside parentheses</li>
	</ul>

	@pre called by match() or eval_quick(), ctp = CTP is at the beginning of an 
	subexpreesion E of filter
	@post ctp is right after E (ctp=CTP+length of E)<br>
	returns true if the expression filter[CTP..ctp-1] matches the task
	@see eval()
	*/
	bool eval();

	/** @brief Evaluate a single expression

	This method only evaluates the subexpression at ctp<br>
	It stops when it finds an OR or AND.

	If it finds a "(", it calls eval() and evaluates the subespression enclosed
	in this parentheses.
	If it filds a "#", it returns whether the Task contains the tag

	@pre called by eval(), ctp is at the beginning of an subexpreesion E
	@post ctp is right after E
	@return true if the expression pointed at by ctp matches the task
	@see eval()
	*/
	bool eval_quick();

	/** @brief Skips unnecessary checks when a true OR is found
	
	When evaluating logical OR, we go from left to right until we find a true
	value. When we find a true value we can skip the remaining checks to the
	right: ((false...) OR[N] true OR[M] (whatever)) is true.<br>
	This function should be called right at OR[M], and skips everything after it
	at the same OR level.
	@pre ctp points to an OR. The left hand value of that or is true
	@post ctp is after the OR
	*/
	void orskip();

	/** @brief Skips unnecessary checks when a true AND is found
	
	When evaluating logical AND, we go from left to right until we find a false
	value. When we find a false value we can skip the remaining checks to the
	right: ((true...) AND[N] false AND[M] (whatever)) is false.<br>
	This function should be called right at AND[M], and skips everything after
	it at the same AND level. (Since AND takes precedence over OR (the
	expression "a AND b or C and D" is equivalent to "(a AND b) or (c AND d)",
	this function stops if it finds an OR) 
	@pre ctp points to an AND. The left hand value of that AND is false
	@post ctp is after the AND
	*/
	void andskip();

	/** @brief Read a tag

	This function reads a tag, moving ctp after it
	@pre ctp is at the beginning of a tag
	@post ctp is after the tag
	@return the tag that has been read
	*/
	string read_tag();

	/** @brief ctp positioning
	
	This function prints the filter expression and shows where
	ctp is pointing to with a little '^' sign. Should only be used for testing

	It also prints a nice message
	<br>
	When not in debug mode, this function does nothing.
	*/
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