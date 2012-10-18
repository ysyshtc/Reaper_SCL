point project_to_line(const point &p, const line &l) {
	return l.s + (l.t - l.s) * (dot(p - l.s, l.t - l.s) / (l.t - l.s).norm2());
}

