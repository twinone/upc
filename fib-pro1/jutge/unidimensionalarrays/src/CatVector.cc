#include <iostream>
#include <vector>

/**
Statement:
Write a function

     vector<int> concatenation(const vector<int>& v1, const vector<int>& v2);
that returns the concatenation of v1 and v2. That is, you must return a vector with the elements of v1 followed by the elements of v2.
*/

using namespace std;

vector<int> concatenation(const vector<int>& v1, const vector<int>& v2) {
	vector<int> r(v1.size()+v2.size());
	for (int i = 0; i < v1.size(); ++i) r[i] = v1[i];
	for (int i = 0; i < v2.size(); ++i) r[i+v1.size()] = v2[i];
	return r;
}

int main() {
	return 0;
}


