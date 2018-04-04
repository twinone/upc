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


void insertion_sort(vector<int>& v) {
	for (int i = 0; i < v.size()-1; ++i) {
		for (int j = i+1; j > 0 and v[j] < v[j-1]; j--) {
			// cout << "swapping pos " << j << ": " << v[j] << " and " << v[j-1] << endl;
			swap(v[j], v[j-1]);
		}
	}
}


int main() {
	int n; cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];

	insertion_sort(v);
	for (int i = 0; i < n; ++i)
		cout << v[i] << " " << endl;


	return 0;
}



