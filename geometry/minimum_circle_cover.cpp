#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>

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
	void out() { printf("(%.5f %.5f)\n", x, y); }
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

struct circle {
	point center;
	double radius;
	circle(point center = point(), double radius = 0) : center(center), radius(radius) {}
};
circle make_circle(const point &a, const point &b) {
	return circle((a + b) / 2, dis(a, b) / 2);
}
circle make_circle(const point &a, const point &b, const point &c) {
	point p = b - a, q = c - a, s(dot(p, p) / 2, dot(q, q) / 2);
	double d = det(p, q);
	point center = a + point(det(s, point(p.y, q.y)), det(point(p.x, q.x), s)) / d;
	return circle(center, dis(center, a));
}
inline bool in_circle(const point &p, const circle &c) {
	return dis(p, c.center) < c.radius + EPS;
}

circle minimum_circle(vector<point> p) {
	circle ret;
	random_shuffle(p.begin(), p.end());
	for (int i = 0; i < (int)p.size(); ++i)
		if (!in_circle(p[i], ret)) {
			ret = circle(p[i], 0);
			for (int j = 0; j < i; ++j)
				if (!in_circle(p[j], ret)) {
					ret = make_circle(p[j], p[i]);
					for (int k = 0; k < j; ++k)
						if (!in_circle(p[k], ret))
							ret = make_circle(p[i], p[j], p[k]);
				}
		}
	return ret;
}

inline point next_point() {
	double x, y;
	scanf("%lf %lf", &x, &y);
	return point(x, y);
}

int main() {
	int task, n;
	scanf("%d", &task);
	for (int task_id = 0; task_id < task; ++task_id) {
		scanf("%d", &n);
		vector<point> p;
		for (int i = 0; i < n; ++i)
			p.push_back(next_point());
		circle ans = minimum_circle(p);
		printf("%.2f\n", ans.radius);
		printf("%.2f %.2f\n", ans.center.x, ans.center.y);
	}
}
