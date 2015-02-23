#include <iostream>
#include <string>

/**
Statement:
Write a function

     bool is_palindrome(const string& s);
that tells if s is a palindrome or not. Remember that a word is a palindrome if it reads the same from left to right than from right to left. In this exercise, s can be rather large; this is why it is passed by reference.

In order to compare the efficiency of your solution against the efficiency of the solution of the Judge, start checking s from its ends.

Observation You only need to submit the required procedure; your main program will be ignored.
*/

using namespace std;
bool is_palindrome(const string& s) {
	for (int i = 0; i < s.size()/2; ++i) {
		if (s[i] != s[s.size()-1-i]) return false;
	}
	return true;
}



int main() {
	string s; cin >> s; cout << is_palindrome(s) << endl;
	return 0;
}


