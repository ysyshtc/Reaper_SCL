bool in_polygon(const point &p, const vector<point> &poly) {
	int n = (int)poly.size();
	int counter = 0;
	for (int i = 0; i < n; ++i) {
		point a = poly[i], b = poly[(i + 1) % n];
		if (point_on_line(p, line(a, b)))
			return false; // bounded excluded
		int x = sign(det(p - a, b - a));
		int y = sign(a.y - p.y);
		int z = sign(b.y - p.y);
		if (x > 0 && y <= 0 && z > 0)
			counter++;
		if (x < 0 && z <= 0 && y > 0)
			counter--;
	}
	return counter != 0;
}

