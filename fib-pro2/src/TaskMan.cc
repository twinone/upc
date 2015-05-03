#include "TaskMan.hh"
#include "comanda.hh"
/** Set to true or false to enable/disable debug messages */

#define ERR_NOT_DONE "No s'ha realitzat"

using namespace std;

TaskMan::TaskMan() {
	DEBUG = false;
}


/** Runs the task manager
Pre:
Post:
*/
void TaskMan::run() {
	bool ok;
	// if llegir() == false, we exit
	while (command.llegir(ok)) {
		if (not ok) continue;
		if (command.es_rellotge()) process_clock();
		else process_task();
	}
}

void TaskMan::process_clock() {
	if (command.es_consulta()) cout << now.to_string() << endl;
	else {
		Clock target = target_clock(now);
		if (target < now) cout << ERR_NOT_DONE << endl;
		else now = target;
	}
}

void TaskMan::process_task() {
	if (command.es_consulta()) {
		build_menu();
		print_menu();
	}
	else if (command.es_insercio()) insert_task();
	else if (command.es_modificacio()) edit_task();
	else if (command.es_esborrat()) delete_task();
}

void TaskMan::build_menu() {
	menu.clear();
	if (calendar.empty()) return;

	// past
	// can't add any filters
	if (command.es_passat()) {
		Clock begin; begin.to_lower_bound();
		add_interval_to_menu(begin, now, false);
		return;
	}
	// present, future
	int dates = command.nombre_dates();
	if (dates == 0) {
		Clock upper; upper.to_upper_bound();
		add_interval_to_menu(now, upper, false);
	}
	else if (dates == 1) {

		string date = command.data(1);
		Clock begin(date, "00:00");
		Clock end(date, "23:59");
		add_interval_to_menu(begin, end, true);
	}
	else if (dates == 2) {
		Clock begin(command.data(1), "00:00");
		Clock end(command.data(2), "23:59");
		add_interval_to_menu(begin, end, true);	
	}

	filter_menu();
}

void TaskMan::filter_menu() {
	// TODO
}

void TaskMan::add_interval_to_menu(Clock begin, Clock end, bool closed) {
	if (DEBUG) cout << "Interval: " << begin.to_string() << " - " << end.to_string() << endl;
	if (end < begin) return;
	Calendar::iterator it = calendar.lower_bound(begin);
	while (it != calendar.end() and it->first < end) { 
		menu.push_back(it);
		++it;
	}
	// add last
	if (closed and it != calendar.end() and it->first == end) menu.push_back(it);
}

void TaskMan::print_menu() const {
	for (int i = 0; i < menu.size(); ++i) {
		Task t = menu[i]->second;
		Clock c = menu[i]->first;
		cout << i+1 << " ";
		cout << t.get_title() << " ";
		cout << c.to_string();
		t.print_tags(" ");
		cout << endl;
	}
}

void TaskMan::insert_task() {
	Clock target = target_clock(now);

	if (not can_insert(target)) { cout << ERR_NOT_DONE << endl; return; }

	Task task(command.titol());
	add_tags(task);
	
	calendar.insert(pair<Clock, Task>(target, task));
}

void TaskMan::add_tags(Task& task) {
	for (int i = 0; i < command.nombre_etiquetes(); ++i)
		task.add_tag(command.etiqueta(i+1));
}

bool TaskMan::can_insert(const Clock& c) const {
	if (c < now) {
		if (DEBUG) cout << "can_insert(): ERR: target in past" << endl;
		return false;
	}

	if (calendar.find(c) != calendar.end()) {
		if (DEBUG) cout << "can_insert(): ERR: exists" << endl;
		return false;
	}

	return true;
}

void TaskMan::edit_task() {
	int task = command.tasca() - 1;
	if (task < 0 or task >= menu.size()) {
		if (DEBUG) cout << "Task (" << task << ") not in range (1-" << menu.size() << ")" << endl;
		cout << ERR_NOT_DONE << endl;
		return;		
	}

	Calendar::iterator target = menu[task];

	if (target == calendar.end()) {
		if (DEBUG) cout << "Target was deleted from menu" << endl;
		cout << ERR_NOT_DONE << endl;
		return;
	}

	if (target->first < now) {
		if (DEBUG) cout << "Target is part of past" << endl;
		cout << ERR_NOT_DONE << endl;
		return;
	}

	// At this point the only thing that can break is an invalid
	// new time/date. Let's do that first
	if (command.te_hora() or command.nombre_dates() == 1) {
		Clock c = target_clock(target->first);
		Task t = target->second;
		if (not can_insert(c)) { cout << ERR_NOT_DONE << endl; return; }

		// unfortunately map's keys are const
		// so we have to erase+insert to change the key
		calendar.erase(target->first);
		// map::insert returns a pair<iterator, bool>
		menu[task] = target = calendar.insert(pair<Clock, Task>(c, t)).first;
	}

	// now change title and or tags
	if (command.te_titol()) target->second.set_title(command.titol());
	add_tags(target->second);
}

// TODO: Deleted elements will point to calendar.end()
void TaskMan::delete_task() {

}

Clock TaskMan::target_clock(Clock c) {
	if (command.nombre_dates() == 1) c.set_date(command.data(1));
	if (command.te_hora()) c.set_time(command.hora());
	return c;
}


void TaskMan::debug() {
	DEBUG = true;
}

