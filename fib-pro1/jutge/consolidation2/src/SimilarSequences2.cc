#include <iostream>

/**
Statement:
In this problem, we say that two sequences of numbers are similar if both have the same sum and finalize with the same number. Provide a program that computes how many of the given sequences are similar to the first (this one included).

In your program, you have to implement and use the following procedure:

void info_sequence(int& sum, int& last);
which reads a sequence from the input and computes the parameters sum and last, the sum of the elements and the last element of the read sequence, respectively.

Input

The input is formed by one or more non-empty sequences of natural numbers all of them strictly positive. Each sequence is finalized by a 0. The end of the input is marked with an empty sequence.

Output

Print how many sequences are similar to the first one, including the first.

Observation

You cannot use strings, vectors or other data structures.
*/

using namespace std;


// Main copied from llista05tardor2014:SequenciesSimilars
int main() {

	int x;
	cin >> x;
	int first_sum = 0;
	int first_last;
	while (x != 0) {
		first_sum += x;
		first_last = x;
		cin >> x;
	}

	int count = 0;
	cin >> x;
	while (x != 0) {
		int sum = 0;
		int last;
		while (x != 0) {
			sum += x;
			last = x;
			cin >> x;
		}
		if (last == first_last && sum == first_sum)
			count++;
		cin >> x;
	}

	cout << (count+1) << endl;



	return 0;
}

