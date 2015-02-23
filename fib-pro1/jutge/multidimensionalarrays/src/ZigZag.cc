#include <iostream>
#include <vector>

/**
Statement:
Write a program that reads several matrices of integer numbers, and that for each one tells whether the result of traversing it in zig-zags is a strictly increasing sequence. We must start at the top-left position, go down the first column, up the second column, down the third column, and so on.

Input

Input consists of several matrices, each with the number of rows r ≥ 1 and the number of columns c ≥ 1, followed by r rows with c integer numbers each.

Output

For every matrix, print its number followed by either “yes” o “no”, depending on whether the zig-zag traversal of the matrix generates a strictly increasing sequence or not.

*/

using namespace std;

typedef vector< vector<int> > Matrix;


int main() {
	int n, m;
	int matnum = 1;
	while (cin >> n >> m) {
		Matrix mat(n, vector<int>(m));
		for (int k = 0; k < n; ++k) {
			for (int l = 0; l < m; ++l) {
				cin >> mat[k][l];
			}
		}
		int old = mat[0][0];
		int i = 0;
		int j = 0;
		int d = 1;
		bool finished = false;
		bool err = false;
		while (not finished and not err) {
			i+=d;
			if (i < 0 or i >= n) { i-=d; ++j; d *= -1; }
			if (j >= m) { finished = true; }
			else {
				if (mat[i][j] <= old) err = true;
				old = mat[i][j];
			}
		}
		if (err) cout << "matriu " << matnum << ": " << "no" << endl;
		else cout << "matriu " << matnum << ": " << "yes" << endl;
		++matnum;
	}

	return 0;
}


