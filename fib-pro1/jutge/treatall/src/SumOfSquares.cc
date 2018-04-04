#include <iostream>

/**
Statement:

*/

using namespace std;

int main() {


	int x;
	cin >> x;
	long result = 0;
	for (int i = 1; i <= x; i++) {
		result += i*i;
	}
	cout << result << endl;
	return 0;
}


