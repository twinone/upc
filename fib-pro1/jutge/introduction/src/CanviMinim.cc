#include <iostream>
#include <vector>

/**
Statement:
Write a program that, given an amount of euros and cents, computes the minimum number of banknotes and coins needed to get that amount. There are coins of 1, 2, 5, 10, 20 and 50 cents and of 1 and 2 euros, and banknotes of 5, 10, 20, 50, 100, 200 and 500 euros.

Input

Input consists of two natural numbers: the number of euros e and the number of cents c. Assume c<100.

Output

Print the number of banknotes and coins of each type that are are needed to represent the amount of the input, so as to minimize the total number of banknotes and coins.


*/

using namespace std;

int main() {

	// We'll work in cents internally, to avoid using floats
	int typesArray[] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
	vector<long> types (typesArray, typesArray + sizeof(typesArray) / sizeof(int));

	vector<long> results;
	results.reserve(types.size());

	long eur;
	int cents;
	cin >> eur >> cents;

	// Convert everything to cents
	eur *= 100;
	eur += cents;

	for (int i = 0; i < types.size(); i++) {

		int type = types[i];
		int num = eur / type;
		if (type > 200) {
			cout << "Banknotes of "<< type/100 <<" euros: " << num << endl;
		} else if (type == 200) {
			cout << "Coins of 2 euros: " << num << endl;
		} else if (type == 100) {
			cout << "Coins of 1 euro: " << num << endl;
		} else if (type > 1) {
			cout << "Coins of "<<type<<" cents: " << num << endl;
		} else {
			cout << "Coins of 1 cent: " << num << endl;
		}


		eur = eur % type;
	}


	return 0;
}


