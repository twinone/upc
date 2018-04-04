#include <iostream>

/**
Statement:
Consider a chess board with r rows and c columns, where every square contains between 0 and 9 coins. Write a program such that, given a chess board, computes the total number of coins on it.

Input

Input begins with the number of rows r and the number of columns c. Follow r lines, each one with c characters between ‘0’ and ‘9’.

Output

Print the total number of coins on the board.
*/

using namespace std;

int main() {
	int r, c;
	cin >> r >> c;

	int sum;
	char x;
	while (cin >> x) {
		sum+=x-'0';
	}
	cout << sum << endl;


	return 0;
}


