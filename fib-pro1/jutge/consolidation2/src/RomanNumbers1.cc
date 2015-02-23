#include <iostream>

/**
Statement:
Write a program that reads several numbers and prints their equivalent Roman number.

Remember that Roman numbers make use seven uppercase letters, which correspond to the following values:

||
Letter	I	V	X	L	C	D	M
Value	1	5	10	50	100	500	1000
||
These are the rules of Roman numbers:

Each decimal digit is computed independently.
Units (1, 2, …, 9) are represented, respectively, I, II, III, IV, V, VI, VII, VIII, IX. Nothing is written for 0.
Tens (10, 20, …, 90) are written like units are, but repacing I by X, V by L, and X by C.
Hundreds (100, 200, …, 900) are written like units are, but repacing I by C, V by D, and X by M.
Thousands (1000, 2000 i 3000) are written like units are, but repacing I by M.
Input

Input consists of several natural numbers between 1 and 3999. (Roman people did not know zero, and the system described above cannot represent numbers greater than or equal to 4000.)

Output

For each number, print its equivalent Roman number.
*/

using namespace std;

void print_digit(int d, char one, char five, char ten) {
	// cout << "printing digit " << d << " ("<<one <<","<<five<<","<<ten<<")"<<endl;
	if (d == 0) return;
	if (d == 9) cout << one << ten;
	else if (d == 4) cout << one << five;
	else {
		if (d >= 5) { cout << five; d-=5; }
		while (d >= 1) { cout << one; d--; }
	}
}
// print the roman digit d*10^p
void print_roman(int d, int p) {
	if (p == 1) print_digit(d, 'I', 'V', 'X');
	else if (p == 2) print_digit(d, 'X', 'L', 'C');
	else if (p == 3) print_digit(d, 'C', 'D', 'M');
	else if (p == 4) while (d >= 1) { cout << 'M'; d--; }
}

int reverse(int n, int &p) {
	int res = 0;
	p = 0;
	while (n > 0) {
		res = res * 10 + n % 10;
		n /= 10;
		p++;
	}
	return res;
}

int main() {
	int x;
	while(cin >> x) {
		int p;
		cout << x << " = ";
		x = reverse(x, p);
		while (x > 0) {
			int d = x % 10;
			print_roman(d, p);
			x /= 10;
			p--;
		}
		cout << endl;
	}

	return 0;
}


