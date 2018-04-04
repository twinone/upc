#include <iostream>
#include <vector>

/**
Statement:
The English mathematician John Conway invented in 1970 the so called "Game of life" as follows: Imagine a square matrix with n rows and n columns with free positions and positions occupied by a bacterium. The game considers the evolution of bacteria with local rules.

From a matrix position, there are considered adjacent positions the (at most eight) positions found at distance one either horizontally, vertically or diagonally. At every moment, every position of the matrix is either empty or contains a bacterium. The rules of the game are the following:

An empty position in an instant t contains a bacterium at time t + 1 if and only if at time t it has exactly three adjacent bacteria.
An occupied position in an instant t contains a bacterium at time t + 1 if and only if at time t it has two or more adjacent bacteria.
We want to make a sequential simulation of the evolution of the game in such a way that, at every moment, only one position is updated. The sequence of positions follows a zig-zag traversal by columns, starting at the upper left position, (0,0), and walking the first column downwards ((0,0) to (n−1,0)), the second column upwards ((n−1,1) to (0,1)), and so on.


We call a round a complete traversal of all the positions in the matrix, following the zig-zag traversal by columns.


Write a program that, for each given matrix and number of rounds, computes the matrix of the game after the stipulated number of rounds.

Note that if after a certain round the matrix has not changed, it will never change again.

Input

The input is formed by two natural numbers n > 0, the size of the matrix, and r>0, the number of rounds. Followed by a list of positions, pairs of integers between 0 and n −1 , indicating the positions of the bacteria .

Output

Write, for each initial configuration, which is the initial matrix of the game and all the intermediate matrices (after each simulation round), with an empty line after each matrix. Follow the format of the examples .

Observation

Note that, if the matrix after a simulation round has not changed, you should not write this matrix more than twice.


*/

using namespace std;

typedef vector< vector<bool> > Matrix;

bool get_cell(Matrix& m, int r, int c) {
	if (r < 0 or c < 0 or r >= m.size() or c >= m.size()) return false;
	return m[r][c];
}

int adj(Matrix& m, int r, int c) {
	int sum = 0;
	for (int i = r-1; i <= r+1; ++i) {
		for (int j = c-1; j <= c+1; ++j) {
			if (!(i == r and j == c)) {
				if (get_cell(m, i, j)) {
					++sum;
				}
			}
			// cout << "adj: " << " r:" << i << " c: " << j << "sum: "<< sum <<endl;
		}
	}
	return sum;
}

bool will_be_alive_in_next_stage(Matrix& m, int r, int c) {
	bool cell = get_cell(m, r, c);
	int a = adj(m, r, c);
	// cout << "row: " << r << " col: " << c << " adj: " << a << endl;
	bool res = (not cell and a == 3) or (cell and a >= 2);
	// cout << "r: " << r << " c: " << c << " adj: " << a << " res: " << res << endl;
	return res;
}

// Returns true if something has changed
bool solve_stage(Matrix& m) {
	bool ret = false;
	int dir = 1;
	for (int i = 0; i < m.size(); ++i) {
		int b = (dir == 1 ? 0 : m.size() -1);
		for (int j = b; j >= 0 and j < m.size(); j += dir) {
			bool curr = m[j][i];
			bool next = will_be_alive_in_next_stage(m, j, i); 
			if (curr != next) ret = true;
			m[j][i] = next;
		}
		dir *= -1;
	}
	return ret;
}

void print_matrix(Matrix& m) {
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m.size(); ++j) {
			cout << (m[i][j] ? 'B' : '.');
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	int n, k;
	cin >> n >> k;
	Matrix m(n);
	for (int i = 0; i < n; ++i)
		m[i] = vector<bool>(n, false);
	int r, c;
	while (cin >> r >> c) {
		m[r][c] = true;
	}

	print_matrix(m);
	int count = 0;
	for (int i = 0; i < k; ++i) {
		// cout << "solving stage, count=" << count << endl;
		if (!solve_stage(m)) ++count;
		else count = 0;
		if (count < 2) {
			print_matrix(m);
		}
	}
	return 0;
}


