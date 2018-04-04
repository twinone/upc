#include <iostream>
#include <vector>
#include <algorithm>

/**
Statement:
Write a program that reads a sequence of natural numbers and that prints, for each one, how many times it appears.

Input

Input consists of a natural number n, followed by n natural numbers between 1000000000 and 1000001000 (both included).

Output

For each number x that appears in the sequence, print how many times it appears, following the format of the example. The output must be sorted in increasing order by x.


*/

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	sort(v.begin(), v.end());
	int t = 1;
	int c = v[0];
	for (int i = 1; i < v.size(); ++i) {
		if (c == v[i]) t++;
		// cout << c << ", " << v[i] << endl;
		if (c != v[i]) {
			cout << c << " : " << t << endl;
			t = 1;
			c = v[i];
		}
		if (i == v.size()-1)
			cout << v[i] << " : " << t << endl;
	}

	return 0;
}


