inline double area_tri(point a, point b) { return det(a, b) / 2; }
inline double area_cir(point a, point b, double radius) {
	double d = atan2(det(a, b), dot(a, b));
	return sqr(radius) * d / 2;
}

inline int intersect(const point &a, const point &b, point &u, point &v, double radius) {
	if (point_to_line(point(0, 0), line(a, b)) + EPS > radius)
		return 0;
	u = line_to_circle(a, b);
	v = line_to_circle(b, a);
	return point_on_line(u, line(a, b)) + point_on_line(v, line(a, b));
}

inline double get(const point &l0, const point &l1, double radius) {
	if (sign(dis(l0, l1)) == 0)
		return 0;
	bool p0 = l0.length() + EPS < radius;
	bool p1 = l1.length() + EPS < radius;
	point a, b;
	if (p0 && p1)
		return area_tri(l0, l1);
	else {
		int check = intersect(l0, l1, a, b, radius);
		if (p0 && !p1)
			return area_tri(l0, b) + area_cir(b, l1, radius);
		else if (!p0 && p1)
			return area_cir(l0, a, radius) + area_tri(a, l1);
		else if (check == 2)
			return area_cir(l0, a, radius) + area_tri(a, b) + area_cir(b, l1, radius);
		else
			return area_cir(l0, l1, radius);
	}
}

inline double polygon_circle_intersect(const vector<point> &a, const circle &c) {
	int n = a.size();
	for (int i = 0; i < n; ++i)
		a[i] = a[i] - center;
	double res = 0;
	a.push_back(a.front());
	for (int i = 0; i < n; ++i)
		res += get(a[i], a[i + 1], c.radius);
	return fabs(res);
}

