#include <iostream>
#include <vector>

/**
Statement:
Let p[0… n] be a vector of integer numbers that contains the coefficients of a polynomial of degree n≥0. For instance, the vector p=⟨3,2,5,−1⟩ represents p(x)=3+2x+5x2−x3, a polynomial of degree n=3.

Write a function

     int evaluate(const vector<int>& p, int x);
that evaluates the polynomial at the point x, that is, that returns ∑i=0n p[i]xi.

Use the Horner scheme:

pnxn+pn−1xn−1+…+p0=((pnx+pn−1)x+…)x+p0.
Observation You only need to submit the required procedure; your main program will be ignored.


*/

using namespace std;

int evaluate(const vector<int>& p, int x) {
	int res = 0;
	int pw = 1;
	for (int i = 0; i < p.size(); ++i) {
		// cout << "res: " << res << " p[i]: " << p[i] << " pw: " << pw << " i: " << i << endl;
		res += p[i] * pw;
		pw *= x;
	}
	return res;
}


int main() {

	vector<int> v(3);
	int x;
	cin >> x;
	cin >> v[0] >> v[1] >> v[2];

	cout << evaluate(v, x) << endl;

	return 0;
}


