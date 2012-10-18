double point_to_line(const point &p, const line &l) {
	return fabs(det(l.t - l.s, p - l.s)) / dis(l.s, l.t);
}

inline double min_point_to_line(const point &a, const line &b) {
	if (dot(b.s - a, b.t - a) < EPS)
		return fabs(det(b.s - a, b.t - a) / b.length());
	return min(dis(a, b.s), dis(a, b.t));
}

