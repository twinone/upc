#include <iostream>
#include <vector>
#include <string>

/**
Statement:

*/

using namespace std;

bool is_palindrome(const string& s) {
	for (int i = 0; i < s.size()/2; ++i) {
		if (s[i] != s[s.size()-1-i]) return false;
	}
	return true;
}


struct Pal {
	string s;
	bool pal;
};

int main() {
	int n;
	cout << "-----" << endl;
	while (cin >> n and n != 0) {
		// cout << "loop" << endl;
		int max = 0;
		vector<Pal> v(n);
		for (int i = 0; i < n; ++i) {
			// cout << "loop2" << endl;
			cin >> v[i].s;
			if (v[i].s.size() >= max) {
				v[i].pal = is_palindrome(v[i].s);
				if (v[i].pal) max = v[i].s.size();
			}
			else v[i].pal = false;
		}
		// cout << "max pal length: " << max << endl;
		bool ok = false;
		for (int i = 0; i < n; ++i) {
			// cout << "loop3" << endl;
			// cout << v[i].s << endl;
			if (v[i].s.size() == max and v[i].pal) {
				ok = true;
				cout << v[i].s << endl;
			}
		}
		if (not ok) cout << "cap palindrom" << endl;
		cout << "-----" << endl;

	}


	return 0;
}


