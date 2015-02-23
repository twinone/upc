
#include <iostream>
#include <sstream>
#include <iomanip> // For setprecision()


/**
Statement:
Write a program that reads a sequence of numbers and prints their average.

Input

Input consists of a non-empty sequence of strictly positive real numbers.

Output

Print the average of the numbers with 2 digits after the decimal point.
*/

using namespace std;

int main() {
	string s;
	double n;
	getline (cin, s);
	stringstream ss(s);

	double total = 0;
	int i = 0;
	while (ss >> n) {
		total+=n;
		i++;
	}
	double avg = total / i;
	cout << setprecision(2) << fixed << avg << endl;
	return 0;
}
