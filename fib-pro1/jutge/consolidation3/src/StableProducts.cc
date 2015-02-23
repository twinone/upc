#include <iostream>
#include <string>
#include <algorithm>

/**
Statement:
The product of x by y is stable if the digits of x and y on one hand, and the digits of x * y on the other hand, are the same ones.

For instance, the product

875 * 650 = 568750
is stable because in the both sides there is a 0, two 5, a 6, a 7 and a 8.

This property can be extended to other bases different of 10. For instance, the product of 3 by 53 is stable in base 2:

11 * 110101 = 10011111
because in both sides there are two 0 and six 1.

Your task is to write a program that, given a sequence of pairs x and y, prints which bases between 2 and 16 (both included) the product x * y is stable for.

To solve this problem, you must implement and use the function

that indicates if, in base b (2≤ b≤ 16), x and y in one hand, and x * y in the other one, have the same digits.

You must implement and use also the procedure

that prints n in base b in the screen (just like that, without spaces nor line feeds).

Input

The input is a sequence of pairs of natural numbers x and y. x ≥ 1, y ≥ 1, x * and ≤ 109 are fulfilled. You can assume this information as a precondition of your procedures.

Output

For each pair x and y, print which bases the product x * y is stable for. If there is not any base, print it. It must print a line feed after the output of each case. Follow the format of the instance.

Observation

If you do tests with random numbers and your program do not find any solution, do not worry: most products are not stable.


*/

using namespace std;

char hex(int n){
	if (n >= 10) {
		return char('A'-10+(n%16));
	}
	else return char('0'+(n%16));
}

string get_hex(int n, int b) {
	string s = "";
	if (n < b) {
		return string(1,hex(n));
	} 
	if (n >= b) {
		return get_hex(n/b, b) + hex(n%b);
	}
	return s;
}


int main() {
	int a, b;
	while (cin >> a >>  b) {
		cout << "solutions for " << a << " and " << b << endl;
		bool one = false;
		for (int i = 2; i <= 16; ++i) {
			string sa = get_hex(a, i);
			string sb = get_hex(b, i);
			string sm = get_hex(a*b, i);

			string cmp_a = sa + sb;
			string cmp_b = sm;
			sort(cmp_a.begin(), cmp_a.end());
			sort(cmp_b.begin(), cmp_b.end());
			if (cmp_a == cmp_b) {
				one = true;
				cout << sa << " * " << sb << " = " << sm << " (base " << i << ")" << endl;
			}
		}
		if (not one) cout << "none of them" << endl;
		cout << endl;
	}


	return 0;
}


