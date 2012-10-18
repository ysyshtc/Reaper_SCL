inline bool point_on_line(const point &a, const line &b) {
	return sign(det(a - b.s, b.t - b.s)) == 0 && dot(b.s - a, b.t - a) < EPS;
}

inline bool two_side(const point &a, const point &b, const line &c) {
	return sign(det(a - c.s, c.t - c.s)) * sign(det(b - c.s, c.t - c.s)) < 0;
}

inline bool intersect_judgement(const line &a, const line &b) {
	if (point_on_line(b.s, a) || point_on_line(b.t, a))
		return true;
	if (point_on_line(a.s, b) || point_on_line(a.t, b))
		return true;
	return two_side(a.s, a.t, b) && two_side(b.s, b.t, a);
}

inline point line_intersect(const line &a, const line &b) {
	double s1 = det(a.t - a.s, b.s - a.s);
	double s2 = det(a.t - a.s, b.t - a.s);
	return (b.s * s2 - b.t * s1) / (s2 - s1);
}

