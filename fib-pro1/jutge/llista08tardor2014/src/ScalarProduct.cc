#include <iostream>
#include <vector>

/**
Statement:
The scalar product of two vectors u=(u0,…,un−1) and v=(v0,…,vn−1) is ∑i=0n−1 ui vi.

Write a function

     double scalar_product(const vector<double>& u, const vector<double>& v);
that returns the scalar product of u and v.

Precondition

The vectors u and v have the same size.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;

double scalar_product(const vector<double>& u, const vector<double>& v) {
	double sum = 0;
	for (int i = 0; i < u.size(); ++i) {
		sum += u[i] * v[i];
	}
	return sum;
}


int main() {
	return 0;
}


