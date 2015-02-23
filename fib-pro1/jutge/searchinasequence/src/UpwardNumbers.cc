#include <iostream>

/**
Statement:
We say that a natural number is upward if its digits fulfill the following property: on the right of a 0 can only be a 1, on the right of a 1 can only be a 2, on the right of a 2 can only be a 3, …, on the right of a 8 can only be a 9 and on the right of a 9 can only be a 0. For instance, 34567 and 8901 are upward, but 1223 and 245 are not.

Your task is to write a program that, given a sequence of natural numbers, indicates if this contains two or more consecutive upward numbers.

Your program must include the function
*/

using namespace std;

bool is_upward(int n) {
	int prev = n % 10;
	while (n >= 10) {
		n /= 10;
		int curr = n % 10;
		if ((curr+1)%10 != prev) {
			return false;
		}
		// cout << "previous: " << prev << " current: " << curr << endl;
		prev = n % 10;
	}

	return true;
}

int main() {
	int x;

	bool prev = false;
	bool pair = false;
	while (!pair && cin >> x) {
		bool curr = is_upward(x);
		if (curr && prev) pair = true;
		prev = curr;
	}

	if (pair) cout << "YES" << endl;
	else cout << "NO" << endl;


	return 0;
}


