#include <iostream>

/**
Statement:
Write a program that reads a prefixed expression, and prints the result of evaluating it. The three possible operators are sum, substraction and multiplication. The operands are natural numbers between 0 and 9 (both included).

Input

Input has a prefixed expression. This means that operators always appear before their operands. For instance, the expression 4 + 3 would be written

+ 4 3
The expression 8 * (4 + 3) would be written

* 8 + 4 3
The expression (2 − 8) * (4 + 3) would be written

* - 2 8 + 4 3
Output

Print a line with an integer number: the result of evaluating the given expression.

Hint

Note that an expression is either a digit or an operator, followed by an expression, followed by another expression. Take inspiration in this fact to write a simple recursive program.
*/

using namespace std;


int process() {
	char c;
	cin >> c;
	if (c >= '0' and c <= '9') return (c - '0');
	else if (c == '+') return process() + process();
	else if (c == '-') return process() - process();
	else if (c == '*') return process() * process();
	else return 0; // should never happen
}

int main() {
	cout << process() << endl;
	return 0;
}


