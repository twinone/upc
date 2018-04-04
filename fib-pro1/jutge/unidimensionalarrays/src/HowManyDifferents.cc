#include <iostream>
#include <vector>
#include <algorithm>

/**
Statement:
Write a program that prints how many different numbers there are in a sequence with n integer numbers.

Input

Input contains different test data. Each test data starts with a natural number n≥1 followed by a sequence with n integer numbers.

Output

For each sequence of the input print, in a line, the number of different elements that contains.*/

using namespace std;


int main() {

	int n;
	while (cin >> n) {
		vector<int> v(n);

		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}
		sort(v.begin(), v.end());

		int sum = 1;
		if (n > 0) {
			for (int i = 0; i < v.size() -1; ++i) {
				if (v[i] != v[i+1]) ++sum;
			}
		}
		cout << sum << endl;

	}
	return 0;
}


