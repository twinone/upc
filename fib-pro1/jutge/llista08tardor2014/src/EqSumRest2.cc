#include <iostream>
#include <vector>

/**
Statement:
Write a program that, given a sequence of integer numbers, tells if there is any number equal to the sum of the rest.

Input

Input contains several cases. Each case begins with a number n≥1 followed by n integer numbers.

Output

For each case, tell if it has a number equal to the sum of the rest.
*/

using namespace std;

int main() {
	int n;
	while (cin >> n) {
		vector<int> v(n);
		int s = 0;
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
			s += v[i];
		}
		bool found = false;
		for (int i = 0; !found and i < n; ++i) {
			if (v[i] == s - v[i]) {
				cout << "YES" << endl;
				found = true;
			}
		}
		if (!found) cout << "NO" << endl;
	}
	return 0;
}