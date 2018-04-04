#include <iostream>
#include <vector>

/**
Statement:
Write a function

     bool exists(int x, const vector<int>& v);
that tells if the integer number x is present in the vector of integer numbers v.

In order to compare the efficiency of your solution against the efficiency of the solution of the Judge, start searching for x from the lowest positions.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;

bool exists(int x, const vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		if (x == v[i]) return true;
	}
	return false;
}

int main() {
	return 0;
}


