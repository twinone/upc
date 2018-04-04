#include <iostream>
#include <string>
#include <vector>

/**
Statement:
Using the declarations

     typedef vector<string> Row;
     typedef vector<Row> Matrix;
write a function

     int number_of_words(const Matrix& m, char c, int k);
that returns how many words w of the Matrix m have the character c at the position k, that is, fulfil @p[k]@ = c (when @p[k]@ exists). Take into account that the “matrix” m is not necessary rectangular, i.e., some rows may be larger than others.

Precondition

k ≥ 0

Observation You only need to submit the required procedure; your main program will be ignored.


*/

using namespace std;


typedef vector<string> Row;
typedef vector<Row> Matrix;

// too slow
int number_of_words(const Matrix& m, char c, int k) {
	int s = 0;
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m[i].size(); ++j) {
			if (k < m[i][j].size() and m[i][j][k] == c) ++s;
		}
	}
	return s;
}


int main() {
	return 0;
}


