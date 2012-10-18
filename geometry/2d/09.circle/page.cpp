struct circle {
	point center;
	double radius;
	circle(point center = point(), double radius = 0) : center(center), radius(radius) {}
};
inline bool operator== (const circle &a, const circle &b) {
	return a.center == b.center && fabs(a.radius - b.radius) < EPS;
}
inline bool operator!= (const circle &a, const circle &b) {
	return a.center != b.center || fabs(a.radius - b.radius) > EPS;
}

inline bool in_circle(const point &p, const circle &c) {
	return dis(p, c.center) < c.radius + EPS;
}

