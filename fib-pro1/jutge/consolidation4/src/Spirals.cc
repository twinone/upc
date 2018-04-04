#include <iostream>
#include <vector>

/**
Statement:
Your task is to write a program that prints “spirals” of size n × n, as it is shown in the
examples.
Input
The input consists of a sequence of natural numbers ended with zero.
Output
For each n, your program must print a spiral of size n × n. Notice that in the row of the
bottom and the column on the rigth there only are ’X’s. Print a line in white after each
spiral.
*/

using namespace std;

typedef vector< vector<bool> > Matrix;

// Returns:
// 0 : out of bounds
// 1 : already active cell
// 2 : empty cell
int get_cell(Matrix& m, int r, int c) {
	if (r < 0 or c < 0 or r >= m.size() or c >= m.size()) return 0;
	return m[r][c] ? 1 : 2;
}


void print_matrix(const Matrix& m) {
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m.size(); ++j) {
			cout << (m[i][j] ? 'X' : '.');
		}
		cout << endl;
	}
}

void line(Matrix& m, int& r, int& c, int& dr, int& dc, int size) {
	for (int i = 1; i <= size; ++i) {
		// cout << "attempt: " << r << "," << c << endl;
		m[r][c] = true;
		r += dr;
		c += dc;
	}
	r -= dr;
	c -= dc;
}

void next_direction(int& dr, int& dc) {
	if (dr == 0) { dr = dc * -1; dc = 0; }
	else { dc = dr; dr = 0; }
}

int main() {
	int n;
	while (cin >> n and n != 0) {
		Matrix m(n, vector<bool>(n));
		int r = n-1;
		int c = 0;
		int dr = 0;
		int dc = 1;
		line(m, r, c, dr, dc, n);
		for (int i = n; i >= 2; --i) {
			// cout << "for" << endl;
			next_direction(dr, dc);
			line(m, r, c, dr, dc, i);
		}
		print_matrix(m);
		cout << endl;
	}
	return 0;
}


