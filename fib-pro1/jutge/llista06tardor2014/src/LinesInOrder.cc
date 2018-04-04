#include <iostream>

/**
Statement:
Write a program that, given a sequence of lines with words, tells which is the first line that has the words in increasing (lexicographic) order.

Input

Input consists of a sequence of lines with words. Each line begins with a number n, followed by n words made up of only lowercase letters.

Output

Print the index of the first line with the words in (not necessary strictly) increasing order. If there is no such line, tell so. Follow the format of the examples.


*/

using namespace std;

int main() {

	int n;
	int index = 0;
	int res_idx = 0;
	// If we don't check res_idx here, the privates will put a lot of nonsense
	// at the end so we keep reading (which loses time)
	while (cin >> n and res_idx == 0) {
		index++;
		string w;
		bool res = true;
		for (int i = 0; i < n; ++i) {
			string ww;
			cin >> ww;
			if (res and res_idx == 0) {
				if (i > 0 && ww < w) res = false;
				else w = ww;
			}
		}
		if (res && res_idx == 0) res_idx = index;
	}
	if (res_idx == 0)  cout << "There is no line in increasing order." << endl;
	else cout << "The first line in increasing order is " << res_idx << "." << endl;

	return 0;
}


