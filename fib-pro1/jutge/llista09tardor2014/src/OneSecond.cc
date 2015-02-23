#include <iostream>

/**
Statement:
Write a program that, given a time expressed in hours, minutes and seconds, computes the time corresponding to add one second, and also the time corresponding to subtract one second.

Your program must use the definition

     struct Time {
         int hour, minute, second;
     };
and it must implement and use the precedure

     void one_second(const Time& t, Time& t1, Time& t2);
that leaves in t1 the time in t plus one second, and leaves in t2 the time in t minus one second. For instance, if t has 23 59 59, then t1 must be 0 0 0 and t2 must be 23 59 58.

Input

Input consists of several cases, each with three numbers (hour, minute and second) that form a correct time. That is, the hour is between 0 and 23, and the minute and the second are between 0 and 59.

Output

For every given time t, print two lines with t1 and t2.

Observation

You can implement auxiliary procedures.
*/

using namespace std;

struct Time {
	int hour, minute, second;
};

void one_second(const Time& t, Time& t1, Time& t2) {
	t1 = t2 = t;
	// Add
	if (++t1.second > 59) {
		t1.second = 0;
		++t1.minute;
	}
	if (t1.minute > 59) {
		t1.minute = 0;
		++t1.hour;
	}
	if (t1.hour > 23) t1.hour = 0;

	// Substract
	if (--t2.second < 0) {
		t2.second = 59;
		--t2.minute;
	}
	if (t2.minute < 0) {
		t2.minute = 59;
		--t2.hour;
	}
	if (t2.hour < 0) t2.hour = 23;

}

void print_time(const Time& t) {
	cout << t.hour << " " << t.minute << " " << t.second << endl;
}

int main() {
	Time t, t1, t2;
	while (cin >> t.hour >> t.minute >> t.second) {
		one_second(t, t1, t2);
		print_time(t1);
		print_time(t2);
	}




	return 0;
}


