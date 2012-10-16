point incenter(const point &a, const point &b, const point &c) {
	double p = (a - b).length() + (b - c).length() + (c - a).length();
	return (a * (b - c).length() + b * (c - a).length() + c * (a - b).length()) / p;
}

