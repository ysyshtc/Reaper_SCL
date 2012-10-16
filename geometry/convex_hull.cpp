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

inline bool turn_left(const point &a, const point &b, const point &c) {
	return det(b - a, c - a) > EPS;
}

inline bool turn_right(const point &a, const point &b, const point &c) {
	return det(b - a, c - a) < -EPS;
}

inline vector<point> convex_hull(vector<point> a) {
	int n = (int)a.size(), cnt = 0;
	sort(a.begin(), a.end());
	vector<point> ret;
	for (int i = 0; i < n; ++i) {
		while (cnt > 1 && turn_left(ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt;
			ret.pop_back();
		}
		ret.push_back(a[i]);
		++cnt;
	}
	int fixed = cnt;
	for (int i = n - 1; i >= 0; --i) {
		while (cnt > fixed && turn_left(ret[cnt - 2], a[i], ret[cnt - 1])) {
			--cnt;
			ret.pop_back();
		}
		ret.push_back(a[i]);
		++cnt;
	}
	// this algorithm will preserve the points which are collineation
	// the lowest point will occur twice, i.e. ret.front() == ret.back()
	return ret;
}

int main() {
	int n;
	double L;
	cin >> n >> L;
	vector<point> a;
	for (int i = 0; i < n; ++i) {
		point tmp;
		tmp.get();
		a.push_back(tmp);
	}
	vector<point> c = convex_hull(a);
	double ans = 0;
	for (int i = 0; i < (int)c.size() - 1; ++i)
		ans += dis(c[i], c[i + 1]);
	ans += 2 * PI * L;
	printf("%.0f\n", ans);
}
