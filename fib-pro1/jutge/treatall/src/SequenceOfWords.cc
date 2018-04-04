#include <iostream>

/**
Statement:
Given a sequence of words, print the length of the longest consecutive subsequence that only contains the first word. That is, if the sequence is s1, …, sn, print

max{j − i + 1 : 1 ≤ i ≤ j ≤ n ∧ si = si+1 = … = sj−1 = sj = s1 } .
Input

Input consists of a non-empty sequence of words.

Output

Print the number of words of the longest consecutive subsequence that only contains the first word.
*/

using namespace std;

int main() {

	// max count of consecutive words
	int max = 1;
	// current streak
	int curr = 1;

	string match,read;
	cin >> match;
	read = match;
	while (cin >> read) {
		if (read == match) curr++;
		else {
			if (curr > max) max = curr;
			curr = 0;
		}
		// cout << "reading " << read << ", max: " << max << ", curr: " << curr << endl;
	}
	if (curr > max) max = curr;
	cout << max << endl;
	return 0;
}


