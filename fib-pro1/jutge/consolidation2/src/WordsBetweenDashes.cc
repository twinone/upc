#include <iostream>

/**
Statement:
Consider a sequence of words formed by letters. The words are separated with dashes, which can appear also at the beginning and in the end of the sequence. The sequence ends with a dot.

Your task is to write a program that prints the number of short words (less than five letters), medium (between five and nine letters), and long (more than nine letters).

Input

The input consists of a line with letters and dashes, finished with a dot.

Output

Your program must print a line with the number of short, medium and long words separated by commas.

Observation

Using |strings| is not allowed in this problem.
*/

using namespace std;

int main() {
	char c = 'a'; // enter loop
	int sc, mc, lc;
	sc = mc = lc = 0;

	int ccc = 0;
	while (c != '.') {
		cin >> c;
		if (c == '-' || c == '.') {
			if (ccc > 9) lc++;
			else if (ccc > 4) mc++;
			else if (ccc > 0) sc++;
			ccc = 0;
		} else {
			ccc++;
		}
	}

	cout << sc << "," << mc << "," << lc << endl;
	return 0;
}


