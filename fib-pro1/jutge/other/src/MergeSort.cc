#include <iostream>
#include <vector>

/**
Statement:

*/

using namespace std;

void print_vector(vector<int> v) {
	for (int i = 0; i < v.size(); ++i) cout << v[i] << " ";
	cout << endl;
}

vector<int> merge(const vector<int>& v1, const vector<int>& v2) {
	int n = v1.size();
	int m = v2.size();
	vector<int> res (n + m);
	int i, j, k;
	i = j = k = 0;
	while (i < n and j < m) {
		if (v1[i] <= v2[j]) { res[k] = v1[i]; ++i; }
		else { res[k] = v2[j]; ++j; }
		++k;
	}
	while (i < n) { res[k] = v1[i]; ++i; ++k; }
	while (j < m) { res[k] = v2[j]; ++j; ++k; }
	return res;
}

vector<int> vec_copy(const vector<int>& v, int start, int end) {
	vector<int> res = vector<int> (end-start);
	for (int i = 0; i < (end-start); ++i) res[i] = v[start+i];
	return res;
}
/*
15
6 2 8 5 10 9 12 1 15 7 3 13 4 11 14
*/
// O(n*log(n))
vector<int> merge_sort(const vector<int>& v) {
	int n = v.size();
	if (n <= 1) return v;
	int m = n / 2;
	vector<int> v1 = vec_copy(v, 0, m);
	vector<int> v2 = vec_copy(v, m, n);
	return merge(merge_sort(v1), merge_sort(v2));
}

vector<int> read() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	return v;
}

int main() {
	vector<int> a = read();

	print_vector(merge_sort(a));

	return 0;
}


