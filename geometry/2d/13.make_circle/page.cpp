circle make_circle(const point &a, const point &b) {
	return circle((a + b) / 2, dis(a, b) / 2);
}
circle make_circle(const point &a, const point &b, const point &c) {
	point center = circumcenter(a, b, c);
	return circle(center, dis(center, a));
}

