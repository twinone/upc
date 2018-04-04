#include <iostream>
#include <vector>

/**
This program is the solution to all of the following problems:
P61473 (Symmetric matrices)
P27498 (Transposed matrices)
P88905 (Product of matrices)
*/

using namespace std;
typedef vector< vector<int> > Matrix;

Matrix alloc_matrix(int r, int c);


void transpose(Matrix& m) {
	int size = m.size();
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < i; ++j) {
			int n = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = n;
		}
	}
}

bool is_symmetric(const Matrix& m) {
	int size = m.size();
	for (int i = 0; i < size; ++i) {
		for (int j = i; j < m.size(); ++j) {
			if (m[i][j] != m[j][i]) return false;
		}
	}
	return true;
}

// From https://github.com/twinone/minimat/blob/master/src/matrix.c
// Yes, my previous teacher used a windows version of gcc that didn't
// compile inline for initializations...
// TMatrix *mMult(TMatrix *m1, TMatrix *m2) {
// 	if (!m1||!m2) { return NULL; }
// 	int r1 = m1->rows;
// 	int c1 = m1->cols;
// 	int r2 = m2->rows;
// 	int c2 = m2->cols;
// 	if (c1 != r2) {
// 		printf("Can't multiply these matrices.\n");
// 		return NULL;
// 	}
// 	TMatrix *res = allocMatrix(r1, c2);
// 	int i;
// 	for (i = 0;i<r1;i++) {
// 		int j;
// 		for (j = 0;j<c2;j++) {
// 			// For each IJ of the resulting matrix:
// 			double resultElement = 0;
// 			int k;
// 			for (k = 0; k < c1; k++) {
// 				resultElement += m1->matrix[i][k] * m2->matrix[k][j];
// 			}
// 			res->matrix[i][j] = resultElement;
// 		}	
// 	}
// 	return res;
// }

Matrix product(const Matrix& a, const Matrix& b) {
	int ra = a.size();
	int ca = a[0].size();
	// int rb = b.size();
	int cb = b[0].size();
	// if (ca != rb) // Error
	Matrix m = alloc_matrix(ra, cb);
	for (int i = 0; i < ra; ++i) {
		for (int j = 0;j < cb; ++j) {	
			// For each IJ of the resulting matrix:
			double r = 0;
			for (int k = 0; k < ca; ++k) {
				r += a[i][k] * b[k][j];
			}
			m[i][j] = r;
		}	
	}
	return m;
}
Matrix alloc_matrix(int r, int c) {
	Matrix m(r);
	for (int i = 0; i < r; ++i) m[i] = vector<int>(c);
	return m;
}


Matrix read_matrix() {
	int r, c;
	cin >> r >> c;
	Matrix m(r);
	for (int i = 0; i < r; ++i) {
		m[i] = vector<int>(c);
		for (int j = 0; j < c; ++j)
			cin >> m[i][j];
	}
	return m;
}

void print_matrix(Matrix& m) {
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m.size(); ++j) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}
int main() {
	Matrix a = read_matrix();
	Matrix b = read_matrix();
	Matrix r = product(a, b);
	print_matrix(r);

	return 0;
}


