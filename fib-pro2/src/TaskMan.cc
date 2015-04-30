#include "TaskMan.hh"
#include "DateTime.hh"
#include "comanda.hh"

using namespace std;

void TaskMan::do_insert() {
	
}

void TaskMan::do_query() {
	
}

void TaskMan::do_delete() {
	
}

TaskMan::TaskMan() {
	
}

/** Runs the task manager
Pre:
Post:
*/
void TaskMan::run() {
	bool ok;
	bool is_exit = false;
	while (comanda.llegir(&ok)) {
		if (comanda.es_insercio()) do_insert();
		if (comanda.es_consulta()) do_query();
		if (comanda.es_esborrat()) do_delete();
		else is_exit = true;
	}
}