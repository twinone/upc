#include <iostream>
#include <cmath>

/**
Statement:
To solve this exercise you will need the definitions and the procedures of the exercises : “” and : “”.

Write a procedure that reads a point:

     void read(Point& p);
which is in the input with the two reals x and y in this order.

Write also a procedure that reads a circle:

     void read(Circle& c);
which is in the input with the three reals x, y, and radius in this order.

Use all this to write a program that reads a circle c and an initial point p, and moves p according to the input, and prints when p go in or go out of c. Suppose that p will never be exactly in the border of c.

Input

Input starts with a line with the circle c (three reals, the last one strictly positive) and a line with the point p (two reals). Then a natural number n comes followed by n lines, each one with a point that indicates the following move of p.

Output

Your program must print the initial situation of p regard to c, and the moments that the point goes in or goes out of the circle. Follow the format of the examples.


*/

using namespace std;

struct Point {
	double x, y;
};

struct Circle {
	Point center;
	double radius;
};


// Returns the absolute value of x
double abs(double x);
// Returns the distance between a and b
double dist(const Point& a, const Point& b);
// Scales a circle to
void scale(Circle& c, double sca);
// Moves the circle c to the coordinates of p
void move(Circle& c, const Point& p);
// Moves p1 by p2 units
void move(Point& p1, const Point& p2);
// Returns true if p is inside the circle c
// Pre: p will never be on the edge of c
bool is_inside(const Point& p, const Circle& c);

void scale(Circle& c, double sca) {
	c.radius *= sca;
}

void move(Circle& c, const Point& p) {
	move(c.center, p);
}

void move(Point& p1, const Point& p2) {
	p1.x += p2.x;
	p1.y += p2.y;
}


double abs(double x) {
	if (x >= 0) return x;
	return -x;
}

double dist(const Point& a, const Point& b) {
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}

bool is_inside(const Point& p, const Circle& c) {
	return dist(c.center, p) < c.radius;
}

void read(Circle& c);
void read(Point& p);

void read(Point& p) {
	cin >> p.x >> p.y;
}
void read(Circle& c) {
	read(c.center);
	cin >> c.radius;
}




int main() {
	Circle c;
	Point p, m;
	read(c);
	read(p);
	int n;
	cin >> n;
	bool inside = is_inside(p, c);
	if (inside) cout << "initially inside" << endl;
	else cout << "initially outside" << endl;
	for (int i = 1; i <= n; ++i) {
		read(m);
		move(p, m);
		bool in = is_inside(p, c);
		if (in != inside) {
			if (in) cout << "in the step " << i << " has gone in" << endl;
			else cout << "in the step " << i << " has gone out" << endl;
			inside = in;
		}
	}

	return 0;
}


