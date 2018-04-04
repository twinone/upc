#include <iostream>
#include <string>
/**
Statement:
Write a program that reads a sequence of words and prints, in reverse order, the second half of the list.

Input

Input consists of a sequence of words.

Output

If n denotes the total number of words, print the ⌈ n/2 ⌉ last words of the original sequence, in reverse order, and one per line.

Observation

For the sake of practice, use recursion (not arrays).

*/

using namespace std;

void read_print(int& n, int& sum) {
	string s;
	bool this_read = cin >> s;
	if (!this_read) {
		// cout << s << endl;
		n = (sum+1) / 2;
		// cout << "final n: " << n << endl;
	} else {
		++sum;
		// cout << "sum++ : "  << sum;
		read_print(n, sum);
		if (n > 0) {
			cout << s << endl;
			n--;
		}
	}
}
int main() {
	int n, sum;
	read_print(n, sum);
	return 0;
}


