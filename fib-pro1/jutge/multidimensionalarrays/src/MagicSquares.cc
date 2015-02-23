#include <iostream>
#include <vector>

/**
Statement:
Once, a messenger of the sultan found a wall with this square filled with numbers:
||

6	1	8
7	5	3
2	9	4
||
Asked, Beremiz told the sultan that it was a “magic square” of order 3, that is, a square of size 3, where all the numbers between 1 and 32 = 9 appear once, and where all the rows, all the columns and the two diagonals add up to the same number, 15 in the example.

Input

Input consists of several cases, each with the order n of a square, followed by n rows, each with n natural numbers between 1 and n2. Assume 1 ≤ n ≤ 100.

Output

For every case, print “yes” if the given square is magic, and “no” otherwise.
*/

using namespace std;

typedef vector<int> Row;
typedef vector<Row> Matrix;

bool has_repeated(Matrix& m) {
	int n = m.size() * m.size();
	vector<int> v(n, 0);
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m.size(); ++j) {
			v[m[i][j]-1] = m[i][j];
		}
	}
	for (int i = 0; i < n; ++i) {
		// cout <	< v[i] << endl;
		if (v[i] != i+1) return true;
	}
	return false;
}
bool is_magic(Matrix& m) {
	int s = m.size();
	if (s == 1) return true;

	int check = 0;
	int check2 = 0;
	for (int i = 0; i < s; ++i) {
		check += m[i][i];
		check2 += m[i][s-1-i];
	}
	if (check != check2) {
		// cout << "diag1 " << check << " != diag2 " << check2 << endl;
		return false;
	}
	int total = 0;
	for (int i = 0; i < s; ++i) {
		int row_sum = 0;
		int col_sum = 0;
		for (int j = 0; j < s; ++j) {
			row_sum += m[i][j];
			col_sum += m[j][i];
			total += m[i][j];
		}
		if (row_sum != check or col_sum != check) {
			// if (row_sum != check) cout << "row " << i << " != " << check << endl;
			// if (col_sum != check) cout << "col " << i << " != " << check << endl;
			return false;
		}
	}
	if (has_repeated(m)) {
		// cout << "total: " << total << " != expected: " <<  expected << endl; 
		return false;
	}
	return true;
}

int main() {
	int n;
	while (cin >> n) {
		Matrix m (n);
		for (int i = 0; i < n; ++i) {
			m[i] = Row(n);
			for (int j = 0; j < n; ++j) {
				cin >> m[i][j];
			}
		}
		cout << (is_magic(m) ? "yes"  : "no") << endl;
	}
	return 0;
}


