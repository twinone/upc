#include <iostream>
#include <vector>

/**
Statement:
Given a matrix, all the elements which are in the first row, in the first
column, in the last row and the last column, form the first layer of the
matrix. Equally, the elements which are in the second row, in the second
column, in the penultimate row and the penultimate column (but that
are not in the first layer), form the second layer. The concept of layer
becomes generalized in the same way for all the elements of the matrix.
For instance, for a matrix with 8 rows and 9 columns, the next diagram shows in which layer
is each element of the matrix:
1 1 1 1 1 1 1 1 1
1 2 2 2 2 2 2 2 1
1 2 3 3 3 3 3 2 1
1 2 3 4 4 4 3 2 1
1 2 3 4 4 4 3 2 1
1 2 3 3 3 3 3 2 1
1 2 2 2 2 2 2 2 1
1 1 1 1 1 1 1 1 1
Your task is to write a program that, given different integer matrices, calculates, for each
one, the values of the minimum and the maximum of all their layers. For instance, for the
matrix
15 1 92 92 82 15 1 92 92
46 31 13 3 32 46 32 13 13
15 3 32 2 22 16 12 34 14
23 17 33 1 2 23 17 32 21
13 63 56 2 21 13 62 66 4
43 9 8 52 11 43 9 8 64
53 96 6 42 17 63 99 6 14
99 94 5 51 21 99 94 5 51
The minimum and the maximum of the first layer are 1 and 99, the minimum and the maximum
of the second layer are 3 and 99, the minimum and the maximum of the third layer are
2 and 62, and the minimum and the maximum of the fourth layer are 1 and 23. We represent
this information with a vector of pairs:
1,99 3,99 2,62 1,23
The main program is already done; do not modify it. Using the types
struct Info {
int min, max;
};
typedef vector<vector<int> > Matrix;
You must implement the function
vector<Info> info layers (const Matrix& mat);
that, given a rectangular matrix mat (with, at least, a row and a column), returns a vector
with as many positions as layers has the matrix, where the position i of the vector contains
the minimum and the maximum values of the layer i+1 of mat.
*/

using namespace std;

struct Info {
	int min, max;
};

typedef vector<vector<int> > Matrix;

vector<Info> info_layers (const Matrix& m) {
	int cols = m[0].size();
	int rows = m.size();
	int ny = (rows+1) / 2;
	int nx = (cols+1) / 2;
	int size = ny < nx ? ny : nx;
	vector<Info> v(size);
	for (int i = 0; i < size; ++i) {
		v[i].min = v[i].max = m[i][i];
		// cout << "min=" <<v[i].min << ",max="<<v[i].max<<" " <<  m[i][i] << " where i = " << i << endl;
		for (int j = i; j < cols-i-1; ++j) {
			cout << "top    pos " << "i=" << i << " j=" << j << "  " << (i) << "," << (i+j)          ;
			if (m[i][i+j]           < v[i].min) {cout << "lt";      v[i].min = m[i][i+j];}
			if (m[i][i+j]           > v[i].max) {cout << "gt";      v[i].max = m[i][i+j];}
					cout << endl;
cout << "bottom pos " << "i=" << i << " j=" << j << "  " << (rows-1-i) << "," << (cols-1-i-j);
			if (m[rows-1-i][cols-1-i-j] < v[i].min) {cout << "lt";      v[i].min = m[rows-1-i][cols-1-i-j];}
			if (m[rows-1-i][cols-1-i-j] > v[i].max) {cout << "gt";      v[i].max = m[rows-1-i][cols-1-i-j];}
				cout << endl;
}
		cout << endl;

		for (int j = i; j < rows-i-1; ++j) {
			cout << "right  pos " << "i=" << i << " j=" << j << "  " << (rows-1-i-j) << "," << (i)     ;
			if (m[rows-1-i-j][i]      < v[i].min) {cout << "lt";      v[i].min = m[rows-1-i-j][i];}
			if (m[rows-1-i-j][i]      > v[i].max) {cout << "gt";      v[i].max = m[rows-1-i-j][i];}
					cout << endl;
cout << "left   pos " << "i=" << i << " j=" << j << "  " << (i+j) << "," << (cols-1-i)     ;
			if (m[i+j][cols-1-i]      < v[i].min) {cout << "lt";      v[i].min = m[i+j][cols-1-i];}
			if (m[i+j][cols-1-i]      > v[i].max) {cout << "gt";      v[i].max = m[i+j][cols-1-i];}
		cout << endl;
		}

	}
	return v;
}


int main() {
	int r, c;
	for (int i = 1; cin >> r >> c; ++i){
		Matrix m(r, vector<int>(c));
		for (int ii = 0; ii < r; ++ii) for (int j = 0; j < c; ++j) cin >> m[ii][j];	
			vector<Info> v = info_layers(m);
		cout << "matriu " << i << ":";
		for (int j = 0; j < v.size(); ++j) {
			cout << " " << v[j].min << "," << v[j].max;
		}
		cout << endl;
	}
	return 0;
}


