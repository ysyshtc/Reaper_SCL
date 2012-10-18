struct node {
	double key; int value;
	node(double k = 0, int v = 0) : key(k), value(v) {}
};
inline bool cmp(const node &a, const node &b) { return a.key + EPS < b.key; }
 
inline void add_interval(vector<node> &s, const double& c1, const double& c2) {
	s.push_back(node(c1, 1));
	s.push_back(node(c2, -1));
}
 
inline bool contain(const circle &a, const circle &b) {
	return a.radius > dis(a.center, b.center) + b.radius - EPS;
}
 
inline bool get_intersect(const circle& a, const circle &b, bool e_trick, vector<node> &s) {
	if (e_trick && a == b) {
		add_interval(s, -PI, PI);
		return true;
	}
	if (contain(a, b))
		return false;
	if (contain(b, a)) {
		add_interval(s, -PI, PI);
		return true;
	}
	point l = b.center - a.center;
	double d = dis(a.center, b.center);
	if (d > a.radius + b.radius - EPS)
		return false;
	double theta = acos((sqr(a.radius) + sqr(d) - sqr(b.radius)) / 2 / a.radius / d);
	double c1 = atan2(l.y, l.x) - theta, c2 = atan2(l.y, l.x) + theta;
	if (c1 < -PI) c1 += 2 * PI;
	if (c2 > PI) c2 -= 2 * PI;
	if (c1 > c2) {
		add_interval(s, c1, PI);
		add_interval(s, -PI, c2);
	}
	else
		add_interval(s, c1, c2);
	return true;
}
 
inline double calc_area(const circle &a, double l, double r) {
	point p = a.center + point(cos(l), sin(l)) * a.radius;
	point q = a.center + point(cos(r), sin(r)) * a.radius;
	return det(p, q) * 0.5 + 0.5 * sqr(a.radius) * (r - l - sin(r - l));
}

inline vector<double> area(const vector<circle> &a) {
	// return the area covered by at least x circlex
	int n = a.size();
	vector<double> ret(n + 1, 0);
	for (int i = 0; i < n; ++i) {
		vector<node> s;
		int part = 0;
		double last;
		for (int j = 0; j < n; ++j)
			get_intersect(a[i], a[j], i < j, s);
		add_interval(s, -PI, PI);
		sort(s.begin(), s.end(), cmp);
		for (int j = 0; j < (int)s.size(); ++j) {
			if (part)
				ret[part] += calc_area(a[i], last, s[j].key);
			part += s[j].value;
			last = s[j].key;
		}
	}
	return ret;
}
 
