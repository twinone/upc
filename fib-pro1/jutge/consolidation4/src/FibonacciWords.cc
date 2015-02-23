#include <iostream>
#include <vector>
#include <string>

/**
Statement:
The words of Fibonacci F1, F2, F3, … are described in the following way:

F1 = “a”.
F2 = “b”.
For every n ≥ 3, Fn is the result of concatenate Fn−2 with Fn−1.
The first seven words of the sequence of Fibonacci are: F1 = “a”, F2 = “b”, F3 = “ab”, F4 = “bab”, F5 = “abbab”, F6 = “bababbab” and F7 = “abbabbababbab”.

Your task is to write a program that, given a sequence of words, prints if they are Fibonacci words or they are not. For those that are it, you must indicate their position in the sequence.

Input

The input is a sequence of words only composed by the letters a and b. None of the words will have more than 1000 letters.

Output

For each Word, your program must indicate its position in the sequence, or print that it is not a word of Fibonacci, following the format of the instance.

Hint

Notice that the length of a word of Fibonacci increases very fast. Therefore, there are few words of Fibonacci having size 1000 or less (in fact, there are exactly 16). Calculate all of them at the beginning of the program.

Observations

Remember that a string s with n characters c can be declared like this: string s(n, c);
Remember also that the string operations like s += ’a’;, s1 += s2; or s = s1 + s2; are not allowed.
*/

using namespace std;

string cat(const string& s1, const string& s2) {
	string res = string(s1.size()+s2.size(), ' ');
	for (int i = 0; i < s1.size(); ++i) {
		res[i] = s1[i];
	}
	for (int i = 0; i < s2.size(); ++i) {
		res[s1.size()+i] = s2[i];
	}
	return res;
}

// string fibo(int n) {
// 	if (n == 1) return "a";
// 	if (n == 2) return "b";
// 	return cat(fibo(n-2), fibo(n-1));
// }

vector<string> words(int n) {
	vector<string> v(n);
	v[0] = "a"; v[1] = "b";
	for (int i = 2; i < n; ++i) v[i] = cat(v[i-2], v[i-1]);
	return v;
}

const int PROBLEM_SIZE = 16;

int main() {
	vector<string> v = words(PROBLEM_SIZE);
	string s;
	while (cin >> s) {
		bool solved = false;
		for (int i = 0; i < PROBLEM_SIZE and not solved; ++i) {
			if (s == v[i]) {
				cout << s << " is the word number " << (i+1) << endl;
				solved = true;
			}
		}
		if (!solved) cout << s << " is not a Fibonacci word" << endl;
	}

	return 0;
}


