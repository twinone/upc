#include <iostream>
#include <vector>

/**
Statement:
Write an efficient recursive function

     int position(double x, const vector<double>& v, int left, int right);
that returns the position of x in the subvector v[left..right]. The function must return −1 if x does not belong to v[left..right] or if left > right.

Precondition

The vector v is sorted in strictly increasing order. Moreover, we have 0 ≤ left ≤ v.size() and −1 ≤ right < v.size().

Observation You only need to submit the required procedure; your main program will be ignored.


*/

using namespace std;


int position(double x, const vector<double>& v, int left, int right) {
	int pos = (left + right)/2;
	// cout << "left" << left << " right " << right << " pos: " << pos << endl;
	if (left > right) return -1;
	if (v[pos] == x) return pos;
	if (left == right) return -1;
	if (v[pos] > x) { return position(x, v, left, pos-1); }
	if (v[pos] < x) { return position(x, v, pos+1, right); }
	return -1;
}


int main() {
	int n, x; cin >> n >> x;
	vector<double> v(n);
	for (int i = 0; i < n; ++i) cin >> v[i];
		cout << "test" << endl;

	cout << position(x, v, 0, v.size()-1);
	return 0;
}


