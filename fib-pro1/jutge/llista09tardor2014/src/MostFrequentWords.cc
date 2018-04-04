#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/**
Statement:
Write a program that reads a sequence of n words and prints the k most frequent (in case of a tie, the smallest in alphabetical order).

Input

Input consists of several cases. Every case starts with n and k, followed by n words made up of only lowercase letters. You can assume that k is between 1 and the number of different words.

Output

For every case, print the k most frequent words in order. Print first the most frequent words, and in case of a tie, the smallest words in lexicographical order. Print a line with 10 dashes at the end of each case.
*/

using namespace std;

struct Word {
	int count;
	string word;
};

bool addnew(vector<Word>& v, int vsize, string s) {
	for (int i = 0; i < vsize; ++i) {
		if (v[i].word == s) {
			++v[i].count;
			return false;
		}
	}
	v[vsize].count += 1;
	v[vsize].word = s;
	return true;
}

bool sort_w(const Word& a, const Word& b) {
	// cout << "comparing " << a.word << " to " << b.word << endl;
	if (a.count != b.count) return a.count > b.count;
	return a.word < b.word;
}


int main() {
	int n, k;
	while (cin >> n >> k) {

		vector<string> v(n);
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}
		sort(v.begin(), v.end());

		int vsize = 0;
		vector<Word> v1(n);
		string w = "";
		for (int i = 0; i < n; ++i) {
			if (w == v[i]) v1[vsize-1].count++;
			else {
				// cout << "new word! " << v[i];
				v1[vsize].word = v[i];
				vsize++;
			}
			w = v[i];
		}

		vector<Word> v2(vsize);
		for (int i = 0; i < vsize; ++i) {
			v2[i] = v1[i];
			// cout << "word: " << v2[i].word << " " << v2[i].count << endl;
		}

		sort(v2.begin(), v2.end(), sort_w);
		for (int i = 0; i < k; ++i) {
			cout << v2[i].word <<  endl;
		}
		cout << "----------" << endl;
	}


}
