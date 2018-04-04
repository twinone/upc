#include <iostream>
#include <vector>
#include <string>

/**
Statement:
Consider a text made up of only lowercase letters, which is encrypted with one of the easiest methods: each letter has an associated character that is always written in its place. Given the translation table and the text encrypted with this table, recover the original text.

Input

Input consists of several cases separated by an empty line. Every case has three parts. The first one is a line with the translation table: 26 different characters (with no spaces nor ‘_’), the first one corresponding to ‘a’, the second one to ‘b’, …, and the last one to ‘z’. The second part is a number n > 0 in a line. The third part consists of n encrypted lines of text.

Output

For each case, write the original text, also with n lines. Change each ‘_’ of the encrypted text for a space. Write an empty line at the end of each case.

Observation

The first example is (basically) extracted from the story “The Gold-Bug” of Edgar Allan Poe. The second text is a famous quotation of Donald Knuth.
*/

using namespace std;

char decrypt(vector<char> e, char c) {
	if (c == '_') return ' ';
	for (int i = 0; i < e.size(); i++) {
		if (e[i] == c) return 'a' + i;
	}
	return '?';
}

int main() {

	vector<char> e(26);
	while (cin >> e[0]) {
		for (int i = 1; i < 26; ++i) {
			cin >> e[i];
		}
		int n;
		cin >> n;
		// cout << "n: " << n << endl;
		for (int i = 0; i < n; ++i) {
			string s;
			cin >> s;
			for (int j = 0; j < s.size(); ++j) {
				s[j] = decrypt(e, s[j]);
			}
			cout << s << endl;
		}
		cout << endl;
	}

	return 0;
}


