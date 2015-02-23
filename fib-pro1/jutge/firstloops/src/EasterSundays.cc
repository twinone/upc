#include <iostream>

/**
Statement:
Easter Sunday is a mobile holiday corresponding to the first Sunday after the first full moon of the spring. Write a program to compute the day D and the month M of the Easter Sunday of every given year Y.

Below, := indicates assignment, div indicates integer division, and mod indicates the remainder of the integer division. To solve this problem, use the Gauss method:

Compute
k := Y div 100
x := Y  mod  19
b := Y  mod  4
c := Y  mod  7
q := k div 4
p := (13+8k) div 25
y := (15−p+k−q)  mod  30
z := (19x+y)  mod  30
n := (4+k−q)  mod  7
e := (2b+4c+6z+n)  mod 7
If z+e ≤ 9, then D := 22+z+e and M := 3.
Otherwise, if z=29 and e=6, then D := 19 and M := 4.
Otherwise, if z=28 and e=6 and x>10, then D := 18 and M := 4.
Otherwise, D := z+e−9 and M := 4.
Input

Input consists of several natural numbers between 1800 and 9999.

Output

Print the day and the month of the Easter Sunday of each year.
*/

using namespace std;

int main() {
	int Y, M, D;
	int k, x, b, c, q, p, y, z, n, e;

	while (cin >> Y) {
		k=Y/100;x=Y%19;b=Y%4;c=Y%7;q=k/4;p=(13+8*k)/25;y=(15-p+k-q)%30;
		z=(19*x+y)%30;n=(4+k-q)%7;e=(2*b+4*c+6*z+n)%7;
		if(z+e<=9){D=22+z+e;M=3;}
		else if(z==29&&e==6){D=19;M=4;}
		else if(z==28&&e==6&&x>10){D=18;M=4;}
		else {D=z+e-9;M=4;}
		cout << D << "/" << M << endl;
	}

	return 0;
}


