point circle_intersect(const circle &a, const circle &b) { // get another point using circle_intersect(b, a)
	point r = (b.center - a.center).unit();
	double d = dis(a.center, b.center);
	double x = .5 * ((sqr(a.radius) - sqr(b.radius)) / d + d);
	double h = sqrt(sqr(a.radius) - sqr(x));
	return a.center + r * x + r.rot90() * h;
}

