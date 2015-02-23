#include <iostream>
#include <float.h>

/**
Statement:

*/

int max(int a, int b) {
	return a > b ? a : b;
}

using namespace std;

int main() {
	cout.setf(ios::fixed);
	cout.precision(4);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int m;
		cin >> m;
		double max = -DBL_MAX;
		double min = DBL_MAX;
		double avg = 0;
		for (int j = 0; j < m; j++) {
			double l;
			cin >> l;
			if (l > max) max = l;
			if (l < min) min = l;
			avg += l;
		}
		avg = avg / m;
		cout << min << " " << max << " " << avg << endl;
	}


	return 0;
}


