#include <iostream>

/**
Statement:
Write a program that reads two numbers a and b, and prints all numbers between a and b.

Input

Input consists of two natural numbers a and b.

Output

Print a line with a,a+1,…,b−1,b. Separate the numbers with commas
*/

using namespace std;

int main() {
	int a, b;

	cin >> a >> b;

	bool comma = false;
	while (a <= b) {
		if (comma) cout << ","; else comma = true;
		cout << a++;
	}
	cout << endl;
	return 0;
}
