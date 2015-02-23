#include <iostream>

/**
Statement:
Given two sequences of non negative integers s1 and s2 both ending in 0, write a program that computes the maximum m of the elements in s1 and that shows the position of its latest occurrence within s1 and the position of its first ocurrence within s2.

In your program, you must implement and use the following procedure:

void infoSequence(int& max, int& lpos);
which reads a sequence ending in 0 and computes the parameters max and lpos. At the end of the execution of the procedure, the parameter max must hold the largest value in the sequence and the parameter lpos has to hold the position of the latest occurrence of the maximum value.

Input

The input is formed by two sequences s1 and s2 of non negative integers, both ending in 0. The sequence s1 is not empty (i.e., it has at least one element different from the ending mark), but the sequence s2 can be empty.

Output

The output is formed by three items: The maximum element in s1, m, the position of the latest occurrence of m in s1, and the position of the first occurrence of m in s2. The case in which m does not form part of s2, or when s2 is an empty sequence (and, therefore m does not form part of s2) must be conveniently indicated.


Please, follow the specified format.
*/

using namespace std;

void infoSequence(int& max, int& lpos) {
	max = lpos = 0;

	int x;
	for (int i = 1; cin >> x && x != 0; i++) {
		if (x >= max) {
			max = x;
			lpos = i;
		}
	}
}



int main() {
	int max, lpos;
	infoSequence(max, lpos);

	cout << max << " " << lpos << " ";
	int x;
	int result = 0;
	for (int i = 1; result == 0 && cin >> x && x != 0; i++) {
		if (x == max) result = i;
	}
	if (result == 0) cout << "-" << endl;
	else cout << result << endl;


	return 0;
}


