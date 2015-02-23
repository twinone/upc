#include <iostream>
#include <cmath>

/**
Statement:
This is another exercise about Fermat’s last theorem, which was explained in the exercise P36430: “Fermat’s last theorem (1)”



Write a program that, given four natural numbers a,b,c,d with a≤ b and c≤ d, prints the number of solutions to the equation

  x2 + y2 = z2
such that a ≤ x ≤ b and c ≤ y ≤ d.

Input

Input has several cases. Each case consists of four natural numbers a, b, c, d such that a≤ b and c≤ d.

Output

For every case, print in a line the number of solutions to the equation

  x2 + y2 = z2
that fulfill a ≤ x ≤ b and c ≤ y ≤ d.


*/
using namespace std;

bool is_int(double a) {
	return a == int(a);
}

int count(int xl, int xh, int yl, int yh) {
	int q = 0;
	for (int i = xl; i <= xh; i++) {
		for (int j = yl; j <= yh; j++) {
			double k = sqrt(i*i + j*j);
			if (is_int(k)) {
				q++;
			}
		}
	}
	return q;
}

int main() {
	int a, b, c, d;
	while (cin >> a >> b >> c >> d) {
		cout << count(a,b,c,d) << endl;		
	}
	return 0;
}


