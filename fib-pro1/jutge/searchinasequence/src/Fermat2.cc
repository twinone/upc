#include <iostream>
#include <cmath>

/**
Statement:
This is another exercise about Fermat’s last theorem. (See the exercise P36430: “Fermat’s last theorem (1)”.)



Write a program such that, given a sequence of lines, each one with four natural numbers a, b, c, d with a≤ b and c≤ d, prints the first natural solution to the equation

  x3 + y3 = z3
that fulfills the restrictions of a line: a≤ x≤ b and c≤ y≤ d.

Input

Input has several lines, each one with four natural numbers a,b,c,d such that a≤ b and c≤ d.

Output

Print a line following the format of the examples, with a natural solution to the equation

  x3 + y3 = z3
that fulfills the restrictions of a line. If there are two or more lines with solution, print the first found. If there are several solutions for the same line, print the one with the smallest x. If there is a tie in x, print the solution with the smallest y. If there are no lines with solution, print “No solution!”.

*/

using namespace std;



int main() {
	int xl, xh, yl, yh;
	bool result = false;
	while (!result && cin >> xl) {
		cin >> xh >> yl >> yh;
		if (xl <= 0 && 0 <= xh) {
			cout << "0^3 + " << yl << "^3 = " << yl << "^3" << endl;
			result = true;
		} else if (yl <= 0 && 0 <= yh) {
			cout  << xl << "^3 + " << "0^3 = " << xl << "^3" << endl;
			result = true;
		}
	}
	if (!result) cout << "No solution!" << endl;

	return 0;
}

