#include <iostream>
#include <cmath>

/**
Statement:
Using the definition

     struct Point {
         double x, y;
     };
write a function

     double dist(const Point& a, const Point& b);
that returns the euclidean distance between two points a and b.

Observation You only need to submit the required classes; your main program will be ignored. Strictly obey the type definitions of the statement.


*/

using namespace std;

struct Point {
	double x, y;
};


double dist(const Point& a, const Point& b) {
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}
int main() {
	Point p1, p2;
	cin >> p1.x >> p1.y >> p2.x >> p2.y;
	cout << dist(p1, p2) << endl;
	return 0;
}


