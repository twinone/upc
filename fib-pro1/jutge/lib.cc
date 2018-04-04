#include <cmath>
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

