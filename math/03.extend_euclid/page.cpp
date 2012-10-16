int64 extend_euclid(int64 a, int64 b, int64 &m, int64 &n) {
	if (b == 0) {
		m = 1; n = 0;
		return a;
	}
	int64 ret = extend_euclid(b, a % b, n, m);
	n -= a / b * m;
	return ret;
}

