#include <iostream>

/**
Statement:
Using the definition

     struct Clock {
         int h;      // hours (0<=h<24)
         int m;      // minutes (0<=m<60)
         int s;      // seconds (0<=s<60)
     };
implement the following functions and procedures:

     Clock midnight();
     void increase(Clock& r);
     void print(const Clock& r);
the function midnight() returns a clock initialized to midnight (00:00:00). The procedure increase() increases the clock a second. The procedure print() prints the time of the clock in the format HH:MM:SS in a line.

Observation You only need to submit the required classes; your main program will be ignored. Strictly obey the type definitions of the statement.


*/

using namespace std;

struct Clock {
	int h;
	int m;
	int s;
};


Clock midnight() {
	Clock c;
	c.h = c.m = c.s = 0;
	return c;
}
void print(const Clock& r) {
	if (r.h < 10) cout << '0';
	cout << r.h;
	cout << ":";
	if (r.m < 10) cout << '0';
	cout << r.m;
	cout << ":";
	if (r.s < 10) cout << '0';
	cout << r.s;
	cout << endl;
}

void increase(Clock& t) {
	if (++t.s > 59) {
		t.s = 0;
		++t.m;
	}
	if (t.m > 59) {
		t.m = 0;
		++t.h;
	}
	if (t.h > 23) t.h = 0;
}



int main() {
	return 0;
}


