#include <iostream>
#include <climits>

/**
Statement:
Write a program that reads sequences of integer numbers and prints the maximum value of each sequence.

Input

Input contains several sequences. Each sequence begins with its number of elements n > 0, followed by n integer numbers.

Output

Print the maximum of every sequence, one per line.
*/

using namespace std;

int main() {

	int num;
	while (cin >> num) {
		int max = INT_MIN;
		for (int i = 0; i < num; i++) {
			int n;
			cin >> n;
			if (n > max) max = n;
		}
		cout << max << endl;
	}


	return 0;
}


