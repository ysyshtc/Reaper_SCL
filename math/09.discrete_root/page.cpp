int primitive_root(int p) {
	int n = p - 1;
	while (true) {
		int root = rand() % (p - 1) + 1, m = n;
		bool found = true;
		for (int i = 0; i < (int)prim.size(); ++i) {
			int cur = prim[i];
			if (m / cur < cur)
				break;
			if (m % cur == 0) {
				if (pow_mod(root, n / cur, p) == 1) {
					found = false;
					break;
				}
				while (m % cur == 0)
					m /= cur;
			}
		}
		if (m > 1)
			if (pow_mod(root, n / m, p) == 1)
				found = false;
		if (found)
			return root;
	}
}

vector<int> discrete_root(int expo, int n, int mod) {
	if (n == 0)
		return vector<int>(1, 0);
	int g = primitive_root(mod);
	int e = discrete_log(g, n, mod);
	int64 u, v;
	int d = extend_euclid(expo, mod - 1, u, v);
	if (e % d != 0)
		return vector<int>();
	int64 delta = (mod - 1) / d;
	u = u * e / d % delta;
	if (u < 0)
		u += delta;
	vector<int> ret;
	while (u < mod - 1) {
		ret.push_back(pow_mod(g, u, mod));
		u += delta;
	}
	return ret;
}

