#include <iostream>
#include <vector>

/**
Statement:
A digital river is a sequence of numbers where the number that follows n is n plus the sum of its digits. For instance,12345 is followed by 12360, because 12345+1+2+3+4+5 = 12360.

If the first number of a digital river is k, then we call this sequence river k. For instance, the river 480 is the sequence 480, 492, 507, 519, ... and the river 483 is the sequence 483, 498, 519, ...

The same as the rivers with water, the digital rivers can meet. This happens when two digital rivers share some of their values. For instance: river 480 meets the river 483 in value 519, and it meets the river 507 in value 507. However, never finds the river 481.

Can be proved that any digital river will meet the river 1, the river 3 or the river 9. For this reason write the function

     int encounter_of_rivers(int n);
that, given a natural number n, returns the first value for which the river n meets the rivers 1, 3 or 9.

Precondition

It is known that 1≤ n ≤16384.

Observation You only need to submit the required procedure; your main program will be ignored.

This problem is from “The British Informatics Olympiad for schools and colleges”.
*/

using namespace std;

int sum_digits(int a) {
	int sum = 0;
	while (a > 0) {
		sum += a % 10;
		a /= 10;
	}
	return sum;
}
vector<bool> precompute(int n) {
}
vector<bool> v = precompute(16384);

int encounter_of_rivers(int n) {
}


int main() {


	return 0;
}


