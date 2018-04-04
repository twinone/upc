#include <iostream>
#include <cmath>

/**
Statement:
To solve this exercise you will need the definitions and the procedures of the exercises : “”, : “” and : “”.

Write a function that prints the relationship that have two given circles c1 and c2:

     int relationship(const Circle& c1, const Circle& c2);
Your function must return 1 if c1 is inside c2, 2 if c2 is inside c1, 3 if any circle in inside the other one but the circles intersect, and 0 otherwise (if the circles do not have any point in common).

Suppose that will never happen any of these extrem cases:

The two circles intersect in a point.
A circle is inside the other one, but shares a point with the border of the bigger circle.
The two circles are equal.
Write a program that reads initial circles c1 and c2, followed by a series of orders, and prints which relationship have c1 and c2 in each step as it is shown in the examples.

Input

Input starts with two lines, one for c1, and the other one for c2, each one with three reals (the third the radius, strictly positive). Then a sequence of lines comes, each one of them starts with an integer i and an order s: i is 1 or 2, i indicates which circle must apply the order to; s is “move” or “scale”. If s is “move”, then two reals that indicate the increase of the coordinates come. If s is “scale”, then a real strictly positive that indicates scale factor comes.

Output

Your program must print the relationship between the two circles at the beginning and in each step, as it is shown in the instance.


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
void read(Circle& c);
void read(Point& p);

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


void read(Point& p) {
	cin >> p.x >> p.y;
}
void read(Circle& c) {
	read(c.center);
	cin >> c.radius;
}



// 0: c1 outside c2
// 1: c1 in c2
// 2: c2 in c1
// 3: intersection
int relationship(const Circle& c1, const Circle& c2) {
	double d = dist(c1.center, c2.center);
	if (d > c1.radius + c2.radius) return 0;
	if (d + c1.radius < c2.radius) return 1;
	if (d + c2.radius < c1.radius) return 2;
	return 3;
}

void print_rel(int rel) {
	if (rel == 0) cout << "circles do not intersect" << endl;
	else if (rel == 1) cout << "the first circle is inside the second one" << endl;
	else if (rel == 2) cout << "the second circle is inside the first one" << endl;
	else cout << "circles intersect" << endl;
}

void process_order(Circle& c) {
	string i;
	cin >> i;
	if (i == "scale") {
		double s;
		cin >> s;
		scale(c, s);
	} else if (i == "move") {
		Point p;
		read(p);
		move(c, p);
	}
}
int main() {
	Circle c1, c2;
	read(c1);
	read(c2);
	print_rel(relationship(c1, c2));

	int n;
	while (cin >> n) {
		if (n == 1) process_order(c1);
		else process_order(c2);
		print_rel(relationship(c1, c2));
	}

	return 0;
}


