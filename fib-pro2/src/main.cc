/** @file main.cc
    @brief Main program
 */

#include "TaskMan.hh"

int main(int argc, char** argv) {
	TaskMan t;
	if (argc > 1 and string(argv[1]) == "--debug") {
		t.debug();
	} 
	t.run();
}