/** @file main.cc
@brief Main program
*/

#include "debug.hh"
#include "TaskMan.hh"
bool DEBUG = false;
	
int main(int argc, char** argv) {
	if (argc > 1 and string(argv[1]) == "--debug") { DEBUG = true; } 

	TaskMan t;
	t.run();
}