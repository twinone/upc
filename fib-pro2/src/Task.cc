#include "Task.hh"


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
