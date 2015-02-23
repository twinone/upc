#include <iostream>
#include <vector>


/**
Statement:
Two natural numbers are twins if the number of appearances of each digit is the same in
each of them. For instance, 25 and 52 are twins, as well as 1225 and 5212. Neither 7899 and
7889, nor 102 and 12 are twins.
Your task is to write a program that says which numbers do not have any twin in a given
set.
Your program must include and use the function
bool are twins(int a, int b );
That indicates if two different natural numbers a and b are twins.
Input
The input is a sequence of cases. Each case starts with a word that identifies it, followed by
a natural number n, followed by n natural numbers strictly positive, all different.
Output
For each input case, print a line starting with the case id, followed by the list of the numbers
which are not twins of any other number of the same case, and ending with the counter
of written numbers. The numbers have to be in the order that they have been given at the
input. Follow the format of the instance
*/

using namespace std;

int num_size(int a) {
	int s = 1;
	while (a >= 10) {
		a /= 10;
		s++;
	}
	return s;
}

bool are_twins(int a, int b) {
	vector<int> v(10, 0);
	while (a > 0 or b > 0) {
		if (a > 0) {
			++(v[a%10]);
			a /= 10;
		}
		if (b > 0) {
			--(v[b%10]);
			b /= 10;
		}
	}
	for (int i = 0; i < 10; ++i) if (v[i] != 0) return false;
		return true;
}

// int main() {
// 	int a, b;
// 	cin >> a >> b;
// 	cout << are_twins(a, b) << endl;

// }
int main() {
	string s;
	while (cin >> s) {
		int n;
		cin >> n;
		vector<int> v(n);
		vector<bool> b(n, false);
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				if (not (b[i] and b[j]) and i != j) {
					if (are_twins(v[i], v[j])) {
						// cout << v[i] << " and " << v[j] << " are twins " << endl;
						b[i] = b[j] = true;
					}
				}
			}
		}
		cout << "Case " << s << ": ";
		int p = 0;
		for (int i = 0; i < n; ++i) {
			if (not b[i]) {
				cout << v[i] << " ";
				++p;

			}
		}
		cout << "(total " << p << ")" << endl;
	}

	return 0;
}


