#include "TaskMan.hh"
#include "comanda.hh"
#include "debug.hh"
/** Set to true or false to enable/disable debug messages */

#define ERR_NOT_DONE "No s'ha realitzat"

using namespace std;

TaskMan::TaskMan() {
	
}

/** Runs the task manager
Pre:
Post:
*/
void TaskMan::run() {
	bool ok;
	// if llegir() == false, we exit
	while (command.llegir(ok)) {
		if (DEBUG and not ok) {
			continue;
		}
		if (command.es_rellotge()) process_clock();
		else process_task();
	}

}

void TaskMan::process_clock() {
	if (command.es_consulta()) {
		now.print();
		cout << endl;
	}
	else {
		Clock tmp = target_clock();
		if (now < tmp) now = tmp;
		else cout << ERR_NOT_DONE << endl;
	}
}

void TaskMan::process_task() {
	if (command.es_consulta()) query_task();
	else if (command.es_insercio()) insert_task();
	else if (command.es_modificacio()) edit_task();
	else if (command.es_esborrat()) delete_task();
}

void TaskMan::query_task() {
	
}

void TaskMan::insert_task() {
	Clock target = target_clock();
	if (not (now < target)) {
		if (DEBUG) cout << "Task is in the past" << endl;
		cout << ERR_NOT_DONE;
		return;
	}

	if (agenda.find(target) == agenda.end()) {
		if (DEBUG) cout << "Task clock already present in map" << endl;
		cout << ERR_NOT_DONE;
		return;
	}

	Task task(command.titol());
	agenda.insert(pair<Clock,Task>(target, task));
}

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
