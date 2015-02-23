#include <iostream>

// Rounding problem
// Copyright 2014 Luuk Willemsen (Twinone)
// For Maria
// Not using math.h (because teachers probably wouldn't let you anyway)


using namespace std;

int main() {
	double x;
	cin >> x;

	long up, down, round;	
	// first get the entire part of it...
	long e = (long) x; // Longs can't have decimal
	// x - e will be the decimal part
	if (x - e == x) {
		cout << "entire number" << endl;
		// in this case the input number has no decimal part
		up = down = round = e;
	} else if (x - e >= 0.5) {
		up = round = e + 1;
		down = e;
	} else {
		// < 0.5
		down = round = e;
		up = e + 1;
	}


	cout << down << " " << up << " " << round << endl;


	return 0;
}


