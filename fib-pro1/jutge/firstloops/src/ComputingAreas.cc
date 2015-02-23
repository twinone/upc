#include <iostream>
#include <sstream>
#include <iomanip> // For setprecision()

/**
Statement:
Write a program that reads several descriptions of rectangles and circles, and for each one prints its corresponding area.

Input

Input begins with a number n, followed by n descriptions. If of a rectangle, we have the word “rectangle” followed by two strictly positive real numbers: its length and its width. If of a circle, we have the word “circle” followed by a strictly positive real number: its radius.

Output

For each description, print its area with 6 digits after the decimal point.
*/

using namespace std;

double PI = 3.14159265358979323846;

int main() {

	double w,h,r;
	string type;
	getline(cin, type);
	stringstream nline(type);
	int n;
	nline >> n;

	for (int i = 0; i < n; i++) {
		string l;
		getline(cin, l);
		stringstream line(l);

		line >> type;
		if (type == "circle") {
			line >> r;
			cout << setprecision(6) << fixed << (PI * r * r) << endl;			
		} else {
			line >> w >> h;
			cout << setprecision(6) << fixed << (w*h) << endl;
		}
	}


	return 0;
}


