#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>

const double EPS = 1e-8;

inline int sign(double x) { return x < -EPS ? -1 : x > EPS; }
inline double sqr(double x) { return x * x; }

struct point {
	double x, y;
	point(double x = 0, double y = 0) : x(x), y(y) {}
	inline double length() const {
		return sqrt(sqr(x) + sqr(y));
	}
	inline point unit() const {
		double len = length();
		return point(x / len, y / len);
	}
	inline point negate() const {
		return point(-x, -y);
	}
	inline point rot90() const { //counter-clockwise
		return point(-y, x);
	}
	inline point _rot90() const { //clockwise
		return point(y, -x);
	}
	inline point rotate(double theta) const { //counter-clockwise
		double c = cos(theta), s = sin(theta);
		return point(x * c - y * s, x * s + y * c);
	}
	int get() { return scanf("%lf %lf", &x, &y); }
	void out() { printf("(%.5f, %.5f)\n", x, y); }
};
inline bool operator== (const point &a, const point &b) {
	return fabs(a.x - b.x) < EPS && fabs(a.y - b.y) < EPS;
}
inline bool operator!= (const point &a, const point &b) {
	return fabs(a.x - b.x) > EPS || fabs(a.y - b.y) > EPS;
}
inline bool operator< (const point &a, const point &b) {
	if (fabs(a.x - b.x) > EPS)
		return a.x < b.x;
	return a.y + EPS < b.y;
}
inline point operator+ (const point &a, const point &b) {
	return point(a.x + b.x, a.y + b.y);
}
inline point operator- (const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
inline point operator* (const point &a, const double &b) {
	return point(a.x * b, a.y * b);
}
inline point operator/ (const point &a, const double &b) {
	return point(a.x / b, a.y / b);
}
inline double det(const point &a, const point &b) {
	return a.x * b.y - b.x * a.y;
}
inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
inline double dis(const point &a, const point &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

struct line {
	point s, t;
	line(point s = point(), point t = point()) : s(s), t(t) {}

	inline double length() const {
		return dis(s, t);
	}
};

