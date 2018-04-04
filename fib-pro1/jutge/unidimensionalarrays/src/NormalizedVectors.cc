#include <iostream>
#include <vector>	

/**
Statement:
A vector of points on the plane is normalized if all the following three conditions hold:

The vector contains at least two different elements.
The sum of all the x-coordinates of the points in the vector equals the sum of all the y-coordinates of the points in the vector.
The barycenter of the points in the vector does not belong to the vector.
Recall that the barycenter of a set of points is the point (x,y) of the plane which has the average value of the x-coordinates of the points as x-coordinate, and the average value of the y-coordinates of the points as y-coordinate.


Make a program that reads vectors of points on the plane and determines whether they are normalized or not.

Your program must use the following definition:

struct Point {

  double x,y;

};

and it must also define, implement and use the following function:

bool barycenter (const vector<Point>& v, Point& b);
which, given a vector of points v, it computes in b the barycenter of the points in v and returns a boolean indicating whether b is to be found in v or not.

Input

The input consists in several lines with sequences. Each sequence describes a vector of points by means of a natural number n>0, which is followed by n pairs of real numbers x1, y1, …, xn, yn describing the coordinates of the n points in the vector.

Output

For each vector of points, the output indicates the barycenter of its points and whether the vector is a normalized one or not. In case the vector is not normalized, the output indicates which of the three required properties of the definition is the first one not holding.


You are asked to follow the output format of the examples.


Real numbers must be written using 2 digits in their fractional part. Use:

cout.setf(ios::fixed);
cout.precision(2);
*/

using namespace std;

struct Point {

	double x,y;

};

// Returns true if v contains it's barycenter b
bool barycenter(const vector<Point>& v, Point& b) {
	b.x = b.y = 0;
	for (int i = 0; i < v.size(); ++i) {
		b.x += v[i].x;
		b.y += v[i].y;
	}
	b.x /= v.size();
	b.y /= v.size();
	for (int i = 0; i < v.size(); ++i) {
		if (v[i].x == b.x and v[i].y == b.y) return true;
	}
	return false;
}

bool diff(const vector<Point>& v) {
	double x = v[0].x;
	double y = v[0].y;
	for (int i = 1; i < v.size(); ++i) {
		if (v[i].x != x or v[i].y != y) return true;
	}
	return false;
}

void print_barycenter(Point& p) {
	cout << "barycenter: (" << p.x << "," << p.y << ")" << endl;
}


int main() {
	cout.setf(ios::fixed);
	cout.precision(2);

	int n;
	while (cin >> n) {
		vector<Point> v(n);
		for (int i = 0; i < n; ++i) {
			double x, y;
			cin >> x >> y;
			v[i].x = x; v[i].y = y;
		}

		Point b;
		bool p3 = !barycenter(v, b);
		print_barycenter(b);
		bool p1 = diff(v);
		bool p2 = b.x == b.y;

		if (!p1) cout << "property 1 does not hold" << endl;
		else if (!p2) cout << "property 2 does not hold" << endl;
		else if (!p3) cout << "property 3 does not hold" << endl;
		else cout << "normalized vector" << endl;
	}
	return 0;
}


