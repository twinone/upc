#include "TaskMan.hh"

/** Set to true or false to enable/disable debug messages */
#define DEBUG true

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
	while (comanda.llegir(&ok)) {
		if (DEBUG and not ok) {
			cerr << "W:"  << endl;
		}
		if (comanda.es_insercio()) do_insert();
		if (comanda.es_consulta()) do_query();
		if (comanda.es_esborrat()) do_delete();
	}
}