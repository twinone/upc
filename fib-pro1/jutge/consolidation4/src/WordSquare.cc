#include <iostream>
#include <vector>

/**
Statement:
A word square of order k is a matrix of k× k letters in form that in each row and in each column a word of the dictionary appears and that the same words are read horizontally and vertically. For instance, below some word squares of order three to eight are given:

  B I T    C A R D    H E A R T    G A R T E R    B R A V A D O    L A T E R A L S
  I C E    A R E A    E M B E R    A V E R S E    R E N A M E D    A X O N E M A L
  T E N    R E A R    A B U S E    R E C I T E    A N A L O G Y    T O E P L A T E
           D A R T    R E S I N    T R I B A L    V A L U E R S    E N P L A N E D
                      T R E N D    E S T A T E    A M O E B A S    R E L A N D E D
                                   R E E L E D    D E G R A D E    A M A N D I N E
                                                  O D Y S S E Y    L A T E E N E R
                                                                   S L E D D E R S
Write a program that reads a dictionary and prints if various matrices of characters are or are not word squares.

Input

Input has two parts:

The first part is a dictionary of n words. First, the value of n is given. Then, n words of the dictionary (all in uppercase letters) come in lexicographical order.

The second part is various matrices of characters. Each matrix starts with an integer k that indicates the number of rows and columns and continues with k2 characters (all uppercase letters) arranged in k rows and k columns. The value k=0 indicates the end on the input.

Output

For each matrix of the input, print “YES” if forms a word square using some of the dictionary words and must print “NO” otherwise.

Observation

In private test data is used a dictionary derived from @/usr/share/dict/words@ with four hundred thousand words and a thousand of matrices are tested.


*/

using namespace std;

typedef vector< vector<char> > Matrix;

bool is_symmetric(Matrix& m) {
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < i ; ++j) {
			if (m[i][j] != m[j][i]) return false;
		}
	}
	return true;
}

bool is_word(string s, vector<string>& v, int left, int right) {
	int pos = (left + right) / 2;
	// cout << "checking word: " << v[pos] << " " <<  s << endl;
	if (v[pos] == s) return true;
	if (left > right) return false;
	if (s < v[pos]) { return is_word(s, v, left, pos-1); }
	if (s > v[pos]) { return is_word(s, v, pos+1, right); }
	return false;
}

string to_string(vector<char> v) {
	string s(v.size(), ' ');
	for (int i = 0; i < v.size(); ++i) s[i] = v[i];
	return s;
}

bool are_all_words(vector<string>& dict, Matrix& m) {
	for (int i = 0; i < m.size(); ++i) {
		if (!is_word(to_string(m[i]), dict, 0, dict.size())) {
			// cout << to_string(m[i]) << " is not a word" << endl;
			return false;
		}
	}
	return true;
}

int main() {

	int n;
	cin >> n;
	vector<string> dict(n);
	for (int i = 0; i < n; ++i) cin >> dict[i];

	while (cin >> n and n != 0) {
		Matrix m(n, vector<char>(n));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> m[i][j];
			}
		}
		if (is_symmetric(m) and are_all_words(dict, m)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}


	return 0;
}