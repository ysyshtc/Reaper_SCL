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

struct point_3d {
	double x, y, z;
	point_3d(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
	inline double length() const {
		return sqrt(sqr(x) + sqr(y) + sqr(z));
	}
	inline point_3d unit() const {
		double len = length();
		return point_3d(x / len, y / len, z / len);
	}
	inline point_3d negate() const {
		return point_3d(-x, -y, -z);
	}
	int get() { return scanf("%lf %lf %lf", &x, &y, &z); }
	void out() { printf("(%.5f, %.5f, %.5f)\n", x, y, z); }
};
inline bool operator== (const point_3d &a, const point_3d &b) {
	return fabs(a.x - b.x) < EPS && fabs(a.y - b.y) < EPS && fabs(a.z - b.z) < EPS;
}
inline bool operator!= (const point_3d &a, const point_3d &b) {
	return fabs(a.x - b.x) > EPS || fabs(a.y - b.y) > EPS || fabs(a.z - b.z) > EPS;
}
inline bool operator< (const point_3d &a, const point_3d &b) {
	if (fabs(a.x - b.x) > EPS)
		return a.x < b.x;
	if (fabs(a.y - b.y) > EPS)
		return a.y < b.y;
	return a.z + EPS < b.z;
}
inline point_3d operator+ (const point_3d &a, const point_3d &b) {
	return point_3d(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline point_3d operator- (const point_3d &a, const point_3d &b) {
	return point_3d(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline point_3d operator* (const point_3d &a, const double &b) {
	return point_3d(a.x * b, a.y * b, a.z * b);
}
inline point_3d operator/ (const point_3d &a, const double &b) {
	return point_3d(a.x / b, a.y / b, a.z / b);
}
inline point_3d det(const point_3d &a, const point_3d &b) {
	return point_3d(a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y);
}
inline double dot(const point_3d &a, const point_3d &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline double dis(const point_3d &a, const point_3d &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z));
}

int main() {
}
