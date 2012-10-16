const int MOD = (15 << 27) + 1; // (3 << 18) + 1
const int ROOT = 31; // 10
vector<int> nth_root;

void transform(vector<int>& a, bool inverse) {
	int n = (int)a.size();
	vector<int> leaf;
	leaf.push_back(0);
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < i; ++j)
			leaf[j + i] = (leaf[j] <<= 1) + 1;
	vector<int> tmp(a);
	for (int i = 0; i < n; ++i)
		a[i] = tmp[leaf[i]];

	for (int step = 1; step < n; step <<= 1) {
		for (int start = 0; start < n; start += step << 1) {
			for (int i = 0; i < step; ++i) {
				long long root = nth_root[(inverse ? n - i * n / 2 / step : i * n / 2 / step) % n];
				long long l = a[start + i], r = root * a[start + step + i] % MOD;
				a[start + i] = (l + r) % MOD;
				a[start + i + step] = (l - r + MOD) % MOD;
			}
		}
	}
}

vector<int> multiply(vector<int> u, vector<int> v) { // the same as the complex version
	nth_root.clear();
	int r = pow_mod(ROOT, (MOD - 1) / n, MOD);
	for (int i = 0, tmp = 1; i < n; ++i) {
		nth_root.push_back(tmp);
		tmp = (long long)tmp * r % MOD;
	}
	int inv = inverse(n, MOD);
	return ret;
}

