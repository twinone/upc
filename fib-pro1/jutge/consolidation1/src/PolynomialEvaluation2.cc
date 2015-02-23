#include <iostream>
#include <math.h>
#include <vector>

/**
Statement:
Write a program that reads a number x and a polynomial p(z) = c0 z0 + c1 z1 + ⋯ + cn zn, and computes p(x).

Input

Input consists of a real number x followed by the description of the polynomial p(z): the real coefficients c0, c1, …, cn in this order. (The first sample input/output corresponds to the evaluation of p(z) = 3 + 4z + 5z2 at x = 2.)

Output

Print p(x) with 4 digits after the decimal point.
*/

using namespace std;


void reverse_vector(std::vector<double>& v) {
	for (int i = 0; i < v.size() / 2; i++) {
		double a = v[i];
		v[i] = v[v.size() - i - 1];
		v[v.size() - i - 1] = a;
	}
}
int main() {
	
	double result = 0;
	double x, tmp;
	cin >> x;

	std::vector<double> v;


	for (int i = 0; cin >> tmp; i++) {
		v.push_back(tmp);
	}

	reverse_vector(v);

	for(int i = 0; i < v.size(); i++) {
		result += v[i] * pow(x, i);
	}

	cout.setf(ios::fixed);
	cout.precision(4);

	cout << result << endl;

	return 0;
}


