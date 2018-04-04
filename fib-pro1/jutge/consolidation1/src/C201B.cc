#include <iostream>

/**
Statement:
The n first lines of multiplication table of a natural number n are given by n multiplicated by one, two, three, …, until n. For instance, being n = 5 we have 5× 1=5, 5× 2=10, 5× 3=15, 5× 4=20, 5× 5=25.

Your task is to write a program that reads a natural number n and prints the n first lines of its multiplication table.

Input

The input is a natural number n.

Output

Your program must print the n first lines of the multiplication table of n, following the format of the instances.
*/

using namespace std;

int main() {
	int x;
	cin >> x;

	for (int i = 1; i <= x; i++) {
		cout << x << " x " << i << " = " << (x*i) << endl;
	}


	return 0;
}


