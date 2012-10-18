inline bool two_side(const point &a, const point &b, const line &c) {
	return sign(det(a - c.s, c.t - c.s)) * sign(det(b - c.s, c.t - c.s)) < 0;
}

vector<point> cut(const vector<point> &c, line p) {
	vector<point> ret;
	if (c.empty())
		return ret;
	for (int i = 0; i < (int)c.size(); ++i) {
		int j = (i + 1) % (int)c.size();
		if (!turn_right(p.s, p.t, c[i]))
			ret.push_back(c[i]);
		if (two_side(c[i], c[j], p))
			ret.push_back(line_intersection(p, line(c[i], c[j])));
	}
	return ret;
}

static const double BOUND = 1e5;
// convex.clear();
// convex.push_back(point(-BOUND, -BOUND));
// convex.push_back(point(BOUND, -BOUND));
// convex.push_back(point(BOUND, -BOUND));
// convex.push_back(point(BOUND, -BOUND));
// convex = cut(convex, line(point, point));
// Judgement: convex.empty();

