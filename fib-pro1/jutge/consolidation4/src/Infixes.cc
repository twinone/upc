#include <iostream>
#include <string>
#include <vector>

/**
Statement:
Your task is to write a program that reads a sequence of words and prints, for each word, all
the other words of the sequence contained in it.
Your program has to implement and use the function
bool contains(string s1, string s2 );
that returns if the word s1 contains the word s2 under the precondition that the length of
s1 is greater or equal than the length of s2.
For instance, contains ("enlightenment", "light"), contains ("enlightenment",
"enlightenment"), contains ("enlightenment", "lighten") and
contains ("enlightenment", "ten") have to return true, but, however, contains
("enlightenment", "ei")
and contains ("enlightenment", "might") have to return false.
Input
Input consists in a natural number n followed by n different words p1, . . . , pn.
Output
The program has to print a line for each p1, . . . , pn in this order. Each line starts with pi
,
followed by the symbol “:” and the list of all the input words contained in pi
, in the same
order than the input. Notice that the list corresponding to each pi always includes pi
, since
every word contains itself.
*/

using namespace std;

bool contains_at(const string& s1, const string& s2, int pos) {
	for (int i = 0; i < s2.size(); ++i) {
		if (s1[pos+i] != s2[i]) return false;
	}
	return true;
}

// Pre s1.size() >= s2
bool contains(string s1, string s2) {
	for (int i = 0; i < s1.size(); ++i) {
		if (contains_at(s1, s2, i)) return true;
	}
	return false;
}


int main() {
	int n; cin >> n;
	vector<string> v(n);
	for (int i = 0; i < n; ++i) cin >> v[i];
	for (int i = 0; i < n; ++i) {
		cout << v[i] << ":";
		for (int j = 0; j < n; ++j) {
			if (contains(v[i], v[j])) cout << " " << v[j];
		}
		cout << endl;
	}


	return 0;
}


