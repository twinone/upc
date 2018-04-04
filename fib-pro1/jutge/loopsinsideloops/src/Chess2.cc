#include <iostream>

/**
Statement:
Consider a chess board with r rows and c columns, where every square contains between 0 and 9 coins. Supose that the upper-left square is white. For instance, this is an empty board with four rows and five columns:

showmover=false, label=false, maxfield=e4

Write a program such that, given a chess board, computes the total number of coins on its white squares.

Input

Input begins with the number of rows r and the number of columns c. Follow r lines, each one with c characters between ‘0’ and ‘9’.

Output

Print the total number of coins on the white squares of the board.
*/

using namespace std;

int main() {
	int r, c;
	cin >> r >> c;

	int sum = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			char x;
			cin >> x;
			if ((i + j) % 2 == 0) {
				sum += x - '0';
				// cout << "Adding" << (x-'0') << endl;
			}
		}
	}

	cout << sum << endl;


	return 0;
}


