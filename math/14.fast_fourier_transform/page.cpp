typedef vector<Complex<double> > VCD;
VCD nth_root;

void transform(VCD& a, bool inverse) {
	int n = (int)a.size();
	for (int step = n / 2; step > 0; step >>= 1) {
		for (int start = 0; start < step; ++start) {
			VCD ret;
			int m = n / step;
			for (int i = 0; i < m; ++i) {
				Complex<double> root = nth_root[i * step];
				if (inverse)
					root = root.conj();
				int index = (i < m / 2 ? i : i - m / 2) * 2 * step;
				ret.push_back(a[start + index] + root * a[start + step + index]);
			}
			for (int i = 0; i < m; ++i)
				a[start + i * step] = ret[i];
		}
	}
}

VCD dot(const VCD& a, const VCD& b) {
	VCD ret;
	int n = (int)a.size();
	for (int i = 0; i < n; ++i)
		ret.push_back(a[i] * b[i]);
	return ret;
}

VCD multiply(VCD u, VCD v) {
	int n = u.size() + (int)v.size() - 1;
	while (low_bit(n) != n)
		n += low_bit(n);
	for (int i = (int)u.size(); i < n; ++i)
		u.push_back(Complex<double>());
	for (int i = (int)v.size(); i < n; ++i)
		v.push_back(Complex<double>());
	nth_root.clear();
	for (int i = 0; i < n; ++i) {
		double theta = 2 * PI * i / n;
		nth_root.push_back(Complex<double>(cos(theta), sin(theta)));
	}

	transform(u, false);
	transform(v, false);

	VCD ret = dot(u, v);
	for (int i = 0; i < n; ++i)
		ret[i] = ret[i] / n;
	transform(ret, true);
	return ret;
}

