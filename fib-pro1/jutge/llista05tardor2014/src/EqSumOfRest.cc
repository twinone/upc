#include <iostream>

/**
Statement:
Write a program that, given a sequence of natural numbers, tells if there is any number equal to the sum of the rest.

Input

Input contains several cases. Each case begins with a number n≥1 followed by n natural numbers.

Output

For each case, tell if it has a number equal to the sum of the rest.


*/

using namespace std;

int main() {

	int n;
	while (cin >> n) {
		int sum = 0;
		int max = 0;
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			sum += x;
			if (x > max) max = x;		
		}
		
		if (max == sum - max) cout << "YES" << endl;
		else cout << "NO" << endl;
	}


	return 0;
}


