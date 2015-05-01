#include "TaskMan.hh"
#include "comanda.hh"
/** Set to true or false to enable/disable debug messages */

#define ERR_NOT_DONE "No s'ha realitzat"

using namespace std;

TaskMan::TaskMan() {
	DEBUG = false;
}

void TaskMan::debug() {
	DEBUG = true;
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
		Clock target = target_clock();
		if (target < now) cout << ERR_NOT_DONE << endl;
		else now = target;
	}
}

void TaskMan::process_task() {
	if (command.es_consulta()) query_tasks();
	else if (command.es_insercio()) insert_task();
	else if (command.es_modificacio()) edit_task();
	else if (command.es_esborrat()) delete_task();
}

void TaskMan::query_tasks() {
	menu.clear();
	if (calendar.empty()) return;

	if (command.es_passat()) {
		for (Calendar::iterator it = calendar.begin(); it != calendar.end() and it->first < now; ++it) {
			menu.push_back(it);
		}
	} else if (command.nombre_dates() == 0) {
		// everything in the future
		for (Calendar::iterator it = calendar.lower_bound(now); it != calendar.end(); ++it) {
			menu.push_back(it);
		}
	}
	print_menu();
}

void TaskMan::print_menu() {
	for (int i = 0; i < menu.size(); ++i) {
		cout << i+1 << " " << menu[i]->second.get_title() << " " << menu[i]->first.to_string() << endl;
	}
}

void TaskMan::insert_task() {
	Clock target = target_clock();
	// TODO: overload >= operator?
	if (target < now) {
		if (DEBUG) cout << "Task is in the past" << endl;
		cout << ERR_NOT_DONE << endl;
		return;
	}

	if (calendar.find(target) != calendar.end()) {
		if (DEBUG) cout << "Task clock already present in map" << endl;
		cout << ERR_NOT_DONE << endl;
		return;
	}

	Task task(command.titol());
	calendar.insert(pair<Clock, Task>(target, task));
}

// TODO:
// Should edit and delete affect the menu also or just the original Agenda?
void TaskMan::edit_task() {
	
}

void TaskMan::delete_task() {
	
}

Clock TaskMan::target_clock() {
	Clock tmp = now;
	if (command.nombre_dates() == 1) tmp.set_date(command.data(1));
	if (command.te_hora()) tmp.set_time(command.hora());
	return tmp;
}



/**
TODO:
Bugs:
----------------
+ 10:30 hi
?
sortir
----------------

*/ 