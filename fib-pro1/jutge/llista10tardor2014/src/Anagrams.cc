#include <iostream>
#include <string>
#include <algorithm>
/**
Statement:

*/

using namespace std;

int main() {

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string p, q;
		p = q = "";
		char c;
		while (cin >> c and c != '.') {
			if (c != ',') p += c;
		}
		while (cin >> c and c != '.') {
			if (c != ',') q += c;
		}
		sort(p.begin(), p.end());
		sort(q.begin(), q.end());
		// cout << p << endl;
		// cout << q << endl;
		if (p == q) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}


