#include <iostream>
#include <string>
/**
Statement:
Your task is to write a program that reads pairs of natural numbers and prints their sum.
Warning: the natural numbers that we consider in this problem can be very large (thousands
of digits), you must store them in variables of string type. The main program is already
done; do not modify it:
int main() {
string x, y;
while (cin >> x >> y) cout << sum(x, y) << endl;
}
Implement the function
string sum(string x, string y );
that, given two strings of characters x and y that represent two natural numbers, returns a
string of characters z that represents their sum.
To simplify the problem, suppose that neither x nor y start with ‘0’. Besides, suppose that x
has, at least, the same number of digits than y. The number of digits of z must be equal to
the number of digits of z plus one, although it causes that z starts with ‘0’.
Observations
• Remember that a string s with n characters c can be declared like this: string s(n,
c);
• Remember also that the string operations like s += ’0’;, s1 += s2; or s = s1 +
s2; are not allowed.
*/

using namespace std;

// Sums two strings of numbers
string sum(string x, string y) {
	string res = string(x.size() +1, '0');
	int carry = 0;
	for (int i = 0; i < res.size(); ++i) {
		int px = x.size()-1-i;
		int py = y.size()-1-i;
		// cerr << "test i" << i << " px: " << px << " py:" << py << endl;
		if (px >= 0) carry += x[x.size()-1-i] - '0';
		if (py >= 0) carry += y[y.size()-1-i] - '0';
		
		res[res.size()-1-i] = (carry % 10) + '0';
		carry /= 10;
	}

	return res;
}



int main() {
	string x, y;
	while (cin >> x >> y) cout << sum(x, y) << endl;
}


