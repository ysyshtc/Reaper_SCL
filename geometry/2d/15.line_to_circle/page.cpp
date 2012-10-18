point line_circle_intersect(const line &l, const circle &c) {
	double x = sqrt(sqr(c.radius) - sqr(point_to_line(c.center, l)));
	return project_to_line(c.center, l) + (l.s - l.t).unit() * x;
}

