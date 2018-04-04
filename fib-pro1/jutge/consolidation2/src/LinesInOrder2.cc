#include <iostream>

/**
Statement:
Write a program that, given a sequence of lines with words, tells which is the last line that has the words in increasing (lexicographic) order.

Input

Input consists of a sequence of lines with words. Each line begins with a number n, followed by n words made up of only lowercase letters.

Output

Print the index of the last line with the words in (not necessary strictly) increasing order. If there is no such line, tell so. Follow the format of the examples.


*/

using namespace std;


int main() {

	int l = 0;
	int n, c;
	for (c = 1; cin >> n; c++) {
		bool res = true;
		// not being allowed to use a continue statement here
		// is just... 
		// frustrating.
		if (n > 0) {
			string s0;
			cin >> s0;
			for (int i = 1; i < n; i++) {
				string s1;
				cin >> s1;
				if (s0 > s1) res = false;
				else s0 = s1;
			}
		}
		if (res) l = c;
	}
	if (l == 0) cout << "There is no line in increasing order." << endl;
	else cout << "The last line in increasing order is " << l << "." << endl;
	return 0;
}


