pair<line, line> tangent(const point &p, const circle &c) {
	circle a = make_circle(p, c.center);
	return make_pair(circle_intersect(a, c), circle_intersect(c, a));
}

