#include <iostream>

/**
Statement:
Write a program that reads Roman numbers and prints their values.

Input

Input consists of several Roman numbers, as explained in the exercise P18298: “Roman numbers (1)”. Every number ends in a period.

Output

For each Roman number, print its value.
*/

using namespace std;


int value_of(char c) {
	if (c == 'I') return 1;
	if (c == 'V') return 5;
	if (c == 'X') return 10;
	if (c == 'L') return 50;
	if (c == 'C') return 100;
	if (c == 'D') return 500;
	if (c == 'M') return 1000;
	return 0;
}
int main() {
	char o;
	while (cin >> o) {
		cout << o;
		int pr, ov;
		ov = pr =  value_of(o);
		int res = 0;
		char n;
		while (cin >> n and n != '.') {
			cout << n;
			// cout << "-----" << endl;
			int nv = value_of(n);
			// cout << "o:  " << o << " n: " << n << " ov: " << ov << " nv: " << nv << endl;
			if (ov == nv) pr += nv;
			else if (ov < nv) { res -= ov; pr = nv; }
			else { res += pr; pr = nv; }
			// cout << "res: " << res << endl;
			ov = nv;

			// cout << "-----" << endl;
		}
		res += pr;
		cout << " = " << res << endl;;

	}
	
	return 0;
}


