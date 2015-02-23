#include <iostream>

/**
Statement:

*/

using namespace std;


double harmonic(int x) {
	if (x == 0) return 0;
	double result = 0;
	for (int i = 1; i <= x; i++) {
		result += (double) 1 / i;
	}
	return result;
}

int main() {

	int n, m;

	cout.setf(ios::fixed);
	cout.precision(10);


	while (cin >> n >> m) {
		// cout << (harmonic(n) - harmonic(m)) << endl;
		double result = 0;
		m++;
		while (m <= n) {
			result += (double) 1 / m;
			m++;
		}
		cout << result << endl;
	}	

	return 0;
}


