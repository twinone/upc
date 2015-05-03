#include <iostream>
#include "Task.hh"

using namespace std;

Task::Task() {}
Task::Task(string title) {
	this->title = title;
}

string Task::get_title() {
	return title;
}

void Task::set_title(string title) {
	this->title = title;
}


bool Task::add_tag(string tag) {
	tags.insert(tag);
}

bool Task::delete_tag(string tag) {
	tags.erase(tag);
}

bool Task::has_tag(string tag) {
	return tags.find(tag) != tags.end();
}

void Task::print_tags(string delim) {
	set<string>::iterator it;
	for (it = tags.begin(); it != tags.end(); ++it) {
		cout << delim << *it;
	}
}

