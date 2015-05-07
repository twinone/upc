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
	ctp = 0;
	return eval();
}

void Filter::dbg_print_pos(string msg) {
	if (!DEBUG) return;
	cout << endl << msg << " (" << ctp << ")" << endl;
	cout << filter << endl;
	for (int i = 0; i < ctp; ++i)
		cout << ' ';
	cout << '^' << endl;
}

// Evaluate a single element
bool Filter::eval_quick() {
	if (filter[ctp] == '(') {
		++ctp;
		bool ret = eval();
		++ctp;
		return ret;
	} else if (filter[ctp] == '#') {
		string tag = read_tag();
		return task.contains(tag);
	}
	else {
		dbg_print_pos("eval_quick(): Expected '#'' or '(': "); return false;
	}


}
bool Filter::eval() {
	bool last = eval_quick();
	while(ctp < filter.size() and (filter[ctp] == '.' or filter[ctp] == ',')) {
		char op = filter[ctp];
		++ctp;
		if (op == OP_OR) {
			if (last) {
				dbg_print_pos("orskip");
				orskip();
				continue;
			} else last = eval_quick();
		} else if (op == OP_AND) {
			if (not last) {
				dbg_print_pos("andskip");
				andskip();
				continue;
			} else last = eval_quick();
		}
	}
	return last;
}


bool Filter::eval_tag() {
	return filter[ctp] == '#' and task.contains(read_tag());
}

// used after a "true or" or a "false and", ignores all same-level expressions
void Filter::orskip() {
	int p = 0;
	while (ctp < filter.size() and p >= 0) {
		if (filter[ctp] == '(') ++p; if (filter[ctp] == ')') --p;
		++ctp;
	}
	--ctp;
	dbg_print_pos("post_orskip:");
}

void Filter::andskip() {
	int p = 0;
	while (ctp < filter.size() and p >= 0) {
		if (filter[ctp] == '(') ++p; if (filter[ctp] == ')') --p;
		if (p == 0 and filter[ctp] == ',') {
			++ctp;
			break;
		}
		++ctp;
	}
	if (filter[ctp] != ',') --ctp;
	dbg_print_pos("post_andskip:");
}

string Filter::read_tag() {
	if (filter[ctp] != '#') {
		dbg_print_pos("read_tag(): expected #:");
		return "";
	}
	string str = "#";
	++ctp; // read #
	while (ctp != filter.size() and
		filter[ctp] != '.' and
		filter[ctp] != ',' and
		filter[ctp] != ':' and
		filter[ctp] != ')' and
		filter[ctp] != '#') 
	{
		str += filter[ctp];
		++ctp;
	}
	// dbg_print_pos("after tag: "+str + ":");
	return str;
}


void Filter::set_filter(const string& filter) { this->filter = filter; }
