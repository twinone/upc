#include <iostream>

/**
Statement:
Consider a square chess board with n rows and n columns, where every square contains between 0 and 9 coins. Write a program such that, given a chess board, computes the total number of coins on its two diagonals.

Input

Input begins with the size n of the board. Follow n lines, each one with n characters between ‘0’ and ‘9’.

Output

Print the total number of coins on the two diagonals of the board.
*/

using namespace std;

int main() {
	int r;
	cin >> r;

	int sum = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < r; j++) {
			char x;
			cin >> x;
			if (i == j || i == r - j - 1) {
				sum += x - '0';
			}
		}
	}

	cout << sum << endl;



	return 0;
}


