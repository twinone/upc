#include <iostream>
#include "Filter.hh"
#include "debug.hh"

using namespace std;

#define OP_AND '.'
#define OP_OR ','

Filter::Filter() {}

// words start with a letter and cannot contain "." "," ":" or "#"
bool Filter::match(const Task& t) {
	this->task = t;
	ctp = begin;
	return eval();
}

void Filter::dbg_print_pos(string msg) {
	if (!DEBUG) return;
	cout << endl << msg << " (" << ctp-begin << ")" << endl;
	for (string::const_iterator it = begin; it != end; ++it) cout << *it;
	for (int i = 0; i < ctp-begin; ++i)
		cout << ' ';
	cout << '^' << endl;
}

// Evaluate a single element
bool Filter::eval_quick() {
	if (*ctp == '(') {
		++ctp;
		bool ret = eval();
		++ctp;
		return ret;
	} else if (*ctp == '#') {
		string tag = read_tag();
		return task.contains(tag);
	}
	else {
		dbg_print_pos("eval_quick(): Expected '#'' or '(': "); return false;
	}


}
bool Filter::eval() {
	bool last = eval_quick();
	while(ctp != end and (*ctp == '.' or *ctp == ',')) {
		char op = *ctp;
		++ctp;
		if (op == OP_OR) {
			if (last) orskip();
			else last = eval_quick();
		}
		else if (op == OP_AND) {
			if (not last) andskip();
			else last = eval_quick();
		}
	}
	return last;
}


// used after a "true or" or a "false and", ignores all same-level expressions
void Filter::orskip() {
	dbg_print_pos("orskip");
	int p = 0;
	while (ctp != end and p >= 0) {
		if (*ctp == '(') ++p; if (*ctp == ')') --p;
		++ctp;
	}
	--ctp;
	dbg_print_pos("post_orskip:");
}

void Filter::andskip() {
	dbg_print_pos("andskip");
	int p = 0;
	while (ctp != end and p >= 0) {
		if (*ctp == '(') ++p; if (*ctp == ')') --p;
		if (p == 0 and *ctp == ',') {
			++ctp;
			break;
		}
		++ctp;
	}
	if (*ctp != ',') --ctp;
	dbg_print_pos("post_andskip:");
}

string Filter::read_tag() {
	if (*ctp != '#') {
		dbg_print_pos("read_tag(): expected #:");
		return "";
	}
	string str = "#";
	++ctp; // read #
	while (ctp != end and
		*ctp != '.' and *ctp != ',' and
		*ctp != ':' and *ctp != ')' and
		*ctp != '#') 
	{
		str += *ctp;
		++ctp;
	}
	// dbg_print_pos("after tag: "+str + ":");
	return str;
}


void Filter::set_filter(const string& filter) { this->begin = filter.begin(); this->end = filter.end(); }
