#include <iostream>
#include <cmath>

/**
Statement:
A famous theorem of the mathematician Pierre de Fermat, proved after more than 300 years, states that, for any natural number n≥ 3, there is no natural solution (except for x= 0 or y= 0) to the equation

  xn + yn = zn .
For n= 2, by contrast, there are infinite non-trivial solutions. For instance, 32 + 42 = 52, 52 + 122 = 132, 62 + 82 = 102, ….



Write a program that, given four natural numbers a,b,c,d with a≤ b and c≤ d, prints a natural solution to the equation

  x2 + y2 = z2
such that a≤ x≤ b and c≤ y≤ d.

Input

Input consists of four natural numbers a, b, c, d such that a≤ b and c≤ d.

Output

Print a line following the format of the examples, with a natural solution to the equation

  x2 + y2 = z2
that fulfills a≤ x≤ b and c≤ y≤ d. If there is more than one solution, print the one with the smallest x. If there is a tie in x, print the solution with the smallest y. If there are no solutions, print “No solution!”.
*/

using namespace std;

bool is_int(double a) {
	return a == int(a);
}

bool solve(int xl, int xh, int yl, int yh, int& x, int& y, int& z) {
	for (int i = xl; i <= xh; i++) {
		for (int j = yl; j <= yh; j++) {
			double k = sqrt(i*i + j*j);
			if (is_int(k)) {
				x = i;
				y = j;
				z = int(k);
				// cout << "sol: " << "x:"<<x << ",y:" << y << k << ": " << z << endl;
				return true;
			}
		}
	}
	return false;
}

int main() {
	int x, y, z;
	int xl, xh, yl, yh;
	cin >> xl >> xh >> yl >> yh;
	
	if (solve(xl, xh, yl, yh, x, y, z)) cout << x << "^2 + " << y << "^2 = " << z << "^2" << endl;
	else cout << "No solution!" << endl;

	return 0;
}


