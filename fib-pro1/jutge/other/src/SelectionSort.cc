#include <iostream>
#include <vector>

/**
Statement:

15
6 2 8 5 10 9 12 1 15 7  3  13 4  11 14

*/

using namespace std;

void swap(int& a, int& b) {
	int tmp = a; a = b; b = tmp;
}

// Pre: v has at least one element
// Returns a sorted vector
// O(n^2)
void selection_sort(vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		int min = v[i], min_pos = i;
		for (int j = i+1; j < v.size(); ++j) {
			if (v[j] < min) {
				min = v[j];
				min_pos = j;
			}
		}
		// cout << "from: " << i << " min: " << min << " minpos: " << min_pos << endl;
  		swap(v[i], v[min_pos]);
	}

}


int main() {
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];

	selection_sort(v);
	for (int i = 0; i < n; ++i)
		cout << v[i] << " " << endl;


	return 0;
}



