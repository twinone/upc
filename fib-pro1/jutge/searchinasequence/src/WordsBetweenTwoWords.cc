#include <iostream>

/**
Statement:
Write a program that, given a sequence of words, prints the number of words between the word “beginning” and the word “end”. If the word “beginning”, the word “end” or both words are missing, or if they appear in inverse order, tell so.

Input

Input consists of several words. The words “beginning” and “end” appear, at most, once.

Output

Print the number of words between the word “beginning” and the word “end”, if these appear in this order. Otherwise, print “wrong sequence”.


*/

using namespace std;

int main() {
	string s;
	bool b = false;
	bool e = false;
	int r = 0;
	while (cin >> s) {
		if (s == "beginning") {
			b = true;
			if (e) { 
				r = -1;
				break;
			} 
		}
		else if (s == "end") {
			e = true;
			if (!b) {
				r = -1;
			}
			// don't keep reading when end is hit
			// or the judge will complain
			break;
		}
		else if (b && !e) r++;
	}
	if (r >= 0 && b && e) cout << r << endl;
	else cout << "wrong sequence" << endl;


	return 0;
}


