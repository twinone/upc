#include <iostream>
#include <string>
#include <vector>

/**
Statement:
Given a sequence of words, we wish to know:

The longest word appearing in the sequence.
All the letters that do not appear in any of its words (the first in the input sequence, when ties occur).
For solving this second item, your program must implement the function

void print_false(const vector<bool>& v);
which prints, for any position i of vector v holding value false, the character with ASCII code ′a′ + i.

Input

The input is formed by a natural n > 0 followed by n non-empty words. Each word is composed exclusively by lowercase letters.

Output

Print the longest word in the input sequence (the first in the input sequence, in case of a tie), followed by the ordered list of lowercase letters that do not appear in any word of the sequence.

Observation

You may find useful to define and use the constant LENGTH_ALPHABET,

const int LENGTH_ALPHABET = ’z’ - ’a’ + 1;

*/

using namespace std;

const int LENGTH_ALPHABET = 'z' - 'a' + 1;


void print_false(const vector<bool>& v) {
	for (int i = 0; i < v.size(); ++i) {
		if (not v[i]) cout << char('a' + i) << endl;;
	}
}


int main() {
	int n;
	cin >> n;
	vector<bool> v(LENGTH_ALPHABET, false);
	int max = 0;
	string l;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		for (int j = 0; j < s.size(); ++j) {
			v[s[j] - 'a'] = true;
			if (s.size() > max) {
				max = s.size();
				l = s;
			}
		}
	}
	cout << l << endl;
	print_false(v);

	return 0;
}


