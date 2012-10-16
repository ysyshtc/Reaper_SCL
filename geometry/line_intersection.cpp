#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

typedef long long ll;

const double EPS = 1e-8;
const double PI = acos(-1.0);
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

inline bool point_on_line(const point &a, const line &b) {
	return sign(det(a - b.s, b.t - b.s)) == 0 && dot(b.s - a, b.t - a) < EPS;
}

inline bool two_side(const point &a, const point &b, const line &c) {
	return sign(det(a - c.s, c.t - c.s)) * sign(det(b - c.s, c.t - c.s)) < 0;
}

inline bool intersection_judgement(const line &a, const line &b) {
	if (point_on_line(b.s, a) || point_on_line(b.t, a))
		return true;
	if (point_on_line(a.s, b) || point_on_line(a.t, b))
		return true;
	return two_side(a.s, a.t, b) && two_side(b.s, b.t, a);
}

inline double point_to_line(const point &a, const line &b) {
	if (dot(b.s - a, b.t - a) < EPS)
		return fabs(det(b.s - a, b.t - a) / b.length());
	return min(dis(a, b.s), dis(a, b.t));
}

inline point line_intersection(const line &a, const line &b) {
	double s1 = det(a.t - a.s, b.s - a.s);
	double s2 = det(a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1);
}

int main() {
	line t1(point(0, 0), point(4, 4));
	line t2(point(3, 2), point(0, 3));

	line_intersection(t1,t2).out();
	cout << intersection_judgement(t1, t2) << endl;
}
