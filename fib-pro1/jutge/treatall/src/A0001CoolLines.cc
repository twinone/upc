#include <iostream>

/**
Statement:
A line of words is cool if its first word, word in the middle and last word are identical.

Your task is to write a program that reads various lines, and prints if all the lines are cool, if there is not any cool line, or if there are some lines that are cool and some that are not.

Input

The input is a sequence of one or more lines. Each line starts with a natural number that indicates its number of words. If this number is even, the middle word does not exist, therefore the line cannot be cool. After the natural number, each line has, at least, two words.

Output

The program has to print “all cool”, “none cool” or “both types” depending on the case.
*/

using namespace std;

void ignore(int n) {
	string s;
	for(int i = 0; i < n; i++) cin >> s;
}
int main() {
	int cool = 0;
	int total = 0;

	int n;
	while (cin >> n) {
		total++;
		if (n == 1) {
			cool++;
			ignore(n);
		}
		else if (n%2 == 0) {
			ignore(n);
		}
		else {
			string cmp;
			bool cooly = true;
			for (int i = 0; i < n; i++) {
				string y;
				cin >> y;
				if (i == 0) { cmp = y; }
				else if (i == n-1 || i == n/2) {
					if (y != cmp) cooly = false;
				}
			}
			if (cooly) cool++;
		}
	}

	if (total == cool) cout << "all cool";
	else if (cool == 0) cout << "none cool";
	else cout << "both types";
	cout << endl;

	return 0;
}


