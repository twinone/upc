#include <iostream>

/**
Statement:
Anna and Bernard play the following game: First, they invent n numbers each. Later, and alternatively, Anna writes her first number, Bernard writes his first number, Anna writes her second number, Bernard writes his second number, and so on. The first to write a number such that its middle digit is not the same as the middle digit of the previous number, loses. (The first number, always Anna’s, may have any middle digit.) If someone writes a number with an even number of digits, he or she loses immedialty. If after writing the 2n numbers nobody loses, the game ends in a draw.

Write a program to decide who wins a game.

Input

Input consists of a natural number n≥ 1, followed by 2n natural numbers a1, b1, …, an, bn: a1 is the first number of Anna, b1 is the first number of Bernard, a2 is the second number of Anna, etcetera.

Output

Print ‘A’, ‘B’, or ‘=’, depending on whether Anna wins, Bernard wins, or it is a tie.
*/

using namespace std;

int middle_digit(int n) {
	if (n == 0) return 0;
	int b = n;
	int num = 0;
	while (n > 0) {
		num++;
		n/=10;
	}
	if (num%2==0) return -1;
	for (int i = 0; i < num/2; i++) {
		b = b / 10;
	}
	return b % 10;
}


int main() {

	int x,y,z; cin >> x;
	cin >> y;
	y = middle_digit(y);
	char winner = 0;
	if (y == -1) winner = 'B';
	for (int i = 1; i < 2*x; i++) {
		cin >> z;
		z = middle_digit(z);

		if (y != z) if (!winner)winner = (i%2==0)?'B':'A';
		if (z == -1) if (!winner)winner = (i%2==0)?'A':'B';

		y = z;
		if (winner)break;
	}
	cout << ((winner) ? winner : '=') << endl;


	return 0;
}


