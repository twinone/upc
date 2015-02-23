#include <iostream>

/**
Statement:
Write a program that reads triples of natural numbers a, b and k, and for each one computes and prints the result of

1
a
 + 	
1
a+k
 + 	
1
a+2k
 + …
for all fractions with denominator smaller than or equal to b.

Input

Input consists of several triples of natural numbers a, b and k, such that 1 ≤ a≤ b and k ≥ 1.

Output

For each triple, print in a line the result of the sum with four digits after the decimal point.
*/

using namespace std;

int main() {
	cout.setf(ios::fixed);
	cout.precision(4);


	int a, b, k;
	while (cin >> a >> b >> k) {
		double res = 0;
		for (int i = 0; a + i*k <= b; ++i) res += (double(1)/(a + i*k)); 
		cout << res << endl;
	}

	return 0;
}


