#include <iostream>
#include <string>
#include <vector>

/**
Statement:
Being v a vector of integer numbers. Starting in any position p of v, jump in the vector according to v[p]: When it is positive, it must jump v[p] steps to the right; when it is negative, it must jump −v[p] steps to the left. The process is always repeated, unless it goes out of bounds.

Write a function

     string exit(int p, vector<int>& v);
that returns “left”, “right” or “never” depending on whether the process goes out of bounds on the left side, on the right side or never ends.

Precondition

0 ≤ p < v.size()

Observation

The value of v at the end is not important. Moreover, notice that the parameter v has not been declared as constant. Take advantage of this fact to write a function as efficient as possible.

Observation You only need to submit the required procedure; your main program will be ignored.


*/

using namespace std;

string exit(int p, vector<int>& v) {
	if (p < 0) return "left";
	if (p >= v.size()) return "right";
	if (v[p] == 0) return "never";
	int j = v[p];
	v[p] = 0;
	return exit(p + j, v);
}


int main() {
	int n, p;
	cin >> n >> p;
	vector<int> v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	cout << exit(p, v) << endl;
	return 0;
}


