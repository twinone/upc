#include <iostream>

/**
Statement:
In this problem, we say that a sequence of natural numbers x1, x2, …, xn is quasi-increasing when, for any i∈{1,…,n−2}, xi < xi+1 or xi < xi+2 (or both conditions).

Note that any sequence with two or less elements is always quasi-increasing. For example, the sequence 1 1 2 3 2 4 1 is quasi-increasing (with length seven), the sequence 1 1 is also quasi-increasing (with length 2), while the sequence 1 1 1 is not.

The quasi-increasing position of a sequence x1, x2, …, xn is the largest k for which the initial subsequence x1, x2, …, xk is quasi-increasing.

Provide a program that, for any given sequence, computes its quasi-increasing position. Furthermore, it should indicate how many sequences are quasi-increasing. Your program must implement and use the following procedure:

void info_sequence(int n, bool& es_qc, int& p_qc);
which reads a sequence with n elements and computes the parameters es_qc and p_qc. The parameter es_qc will become true whenever the sequence is quasi-increasing. The parameter p_qc indicates the quasi-increasing position of the just read sequence.

Input

The input is formed by several sequences of natural numbers. Each sequence is preceded by its length, which is at least 2. The last sequence has length zero, and should not be processed.

Output

Print the quasi-increasing position, for each given sequence, and the number of given sequences that are quasi-increasing.

Observation

You cannot use strings, vectors or other data structures.

Take into account that, as all the input sequences have at least two elements, their quasi-increasing position is greater than or equal to 2.
*/

using namespace std;

int main() {

	int n;
	int t = 0;
	while (cin >> n && n != 0) {
		int a, b;
		cin >> a >> b;
		bool err = false;
		int p = 2;
		for (int i = 1; i < n - 1; i++) {
			int c;
			cin >> c;
			if (a >= b && a >= c) {
				if (a >= b) err = true;
			} else if (!err) {
				a = b;
				b = c;
				++p;
			}
		}
		if (p == n) ++t;
		cout << p << endl;
	}
	cout << "Quasi-increasing: " << t << endl;

	return 0;
}


