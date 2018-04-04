#include <iostream>
#include <vector>

/**
Statement:

*/

using namespace std;

vector<bool> primes_up_to(int n) {
	vector<bool> v(n+1, true);
	v[0] = v[1] = false;
	for (int i = 2; i*i <= n; ++i)
		if (v[i]) 
			for (int j = 2*i; j <= n; j+=i)
				v[j] = false;
	return v;
}

void print_vector(vector<bool> v) {
	for (int i = 0; i < v.size(); ++i) {
		if (v[i]) cout << i << endl;
	}
}

int main() {

	int n;
	cin >> n;
	print_vector(primes_up_to(n));

	return 0;
}


