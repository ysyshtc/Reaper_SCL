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

inline bool turn_left(const point &a, const point &b, const point &c) {
	return det(b - a, c - a) > EPS;
}

inline bool turn_right(const point &a, const point &b, const point &c) {
	return det(b - a, c - a) < -EPS;
}

inline bool two_side(const point &a, const point &b, const line &c) {
	return sign(det(a - c.s, c.t - c.s)) * sign(det(b - c.s, c.t - c.s)) < 0;
}

inline point line_intersection(const line &a, const line &b) {
	double s1 = det(a.t - a.s, b.s - a.s);
	double s2 = det(a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1);
}

vector<point> cut(const vector<point> &c, line p) {
	vector<point> ret;
	if (c.empty())
		return ret;
	for (int i = 0; i < (int)c.size(); ++i) {
		int j = (i + 1) % (int)c.size();
		if (!turn_right(p.s, p.t, c[i]))
			ret.push_back(c[i]);
		if (two_side(c[i], c[j], p))
			ret.push_back(line_intersection(p, line(c[i], c[j])));
	}
	return ret;
}

static const double BOUND = 1e5;
// convex.clear();
// convex.push_back(point(-BOUND, -BOUND));
// convex.push_back(point(BOUND, -BOUND));
// convex.push_back(point(BOUND, -BOUND));
// convex.push_back(point(BOUND, -BOUND));
// convex = cut(convex, line(point, point));
// Judgement: convex.empty();

point next_point() {
	double x, y;
	scanf("%lf %lf", &x, &y);
	return point(x, y);
}

int main() {
	int task, n;
	scanf("%d", &task);
	for (int task_id = 0; task_id < task; ++task_id) {
		scanf("%d", &n);
		vector<point> convex, poly;
		for (int i = 0; i < n; ++i)
			poly.push_back(next_point());
		convex.push_back(point(-BOUND, -BOUND));
		convex.push_back(point(BOUND, -BOUND));
		convex.push_back(point(BOUND, BOUND));
		convex.push_back(point(-BOUND, BOUND));
		reverse(poly.begin(), poly.end());
		for (int i = 0; i < n; ++i)
			convex = cut(convex, line(poly[i], poly[(i + 1) % (int)poly.size()]));
		double sum = 0;
		for (int i = 0; i < (int)convex.size(); ++i)
			sum += det(convex[i], convex[(i + 1) % (int)convex.size()]);
		printf("%.2f\n", sum / 2);
	}
}
