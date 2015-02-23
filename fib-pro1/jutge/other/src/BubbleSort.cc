#include <iostream>
#include <vector>

/**

15
6 2 8 5 10 9 12 1 15 7  3  13 4  11 14
1 2 3 4 5  6 7  8 9  10 11 12 13 14 15

Moves the biggest int to the end by pairs

*/

using namespace std;

// Returns the vector v, sorted in increasing order
// "Even Obama knows this algorithm"
// O((n^2 + n)/2) = O(n^2)
void bubble_sort(vector<int>& v) {
	for (int j = v.size()-1; j >= 1; --j) {
		for (int i = 0; i < j; ++i) {
			if (v[i] > v[i+1]) {
				// cout << "swapping pos " << i << "(" << v[i] << ") and pos " << i+1 << "(" <<  v[i+1] << ")" << endl;
				int tmp = v[i+1];
				v[i+1] = v[i];
				v[i] = tmp;
			}
		}
	}
}


int main() {
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];

	bubble_sort(v);
	for (int i = 0; i < n; ++i)
		cout << v[i] << " " << endl;


	return 0;
}


