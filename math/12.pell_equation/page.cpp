pair<int64, int64> solve_pell64(int64 n) {
	const static int MAXC = 111;
	int64 p[MAXC], q[MAXC], a[MAXC], g[MAXC], h[MAXC];
	p[1] = 1; p[0] = 0;
	q[1] = 0; q[0] = 1;
	a[2] = square_root(n);
	g[1] = 0; h[1] = 1;
	for (int i = 2; ; ++i) {
		g[i] = -g[i - 1] + a[i] * h[i - 1];
		h[i] = (n - g[i] * g[i]) / h[i - 1];
		a[i + 1] = (g[i] + a[2]) / h[i];
		p[i] = a[i] * p[i - 1] + p[i - 2];
		q[i] = a[i] * q[i - 1] + q[i - 2];
		if (p[i] * p[i] - n * q[i] * q[i] == 1)
			return make_pair(p[i], q[i]);
	}
}

