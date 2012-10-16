bool test(int64 n, int base) {
	int64 m = n - 1, ret = 0;
	int s = 0;
	for (; m % 2 == 0; ++s)
		m >>= 1;
	ret = pow_mod(base, m, n);
	if (ret == 1 || ret == n - 1)
		return true;
	for (--s; s >= 0; --s) {
		ret = multiply_mod(ret, ret, n);
		if (ret == n - 1)
			return true;
	}
	return false;
}

int64 special[7] = {
	1373653LL,
	25326001LL,
	3215031751LL,
	25000000000LL,
	2152302898747LL,
	3474749660383LL,
	341550071728321LL
};

bool is_prime(int64 n) {
	if (n < 2)
		return false;
	if (n < 4)
		return true;

	if (!test(n, 2) || !test(n, 3))
		return false;
	if (n < special[0])
		return true;

	if (!test(n, 5))
		return false;
	if (n < special[1])
		return true;

	if (!test(n, 7))
		return false;
	if (n == special[2])
		return false;
	if (n < special[3])
		return true;

	if (!test(n, 11))
		return false;
	if (n < special[4])
		return true;

	if (!test(n, 13))
		return false;
	if (n < special[5])
		return true;

	if (!test(n, 17))
		return false;
	if (n < special[6])
		return true;

	return test(n, 19) && test(n, 23) && test(n, 29) && test(n, 31) && test(n, 37);
}

vector<int64> merge(const vector<int64> &a, const vector<int64> &b) {
	vector<int64> ret;
	for (int i = 0; i < (int)a.size(); ++i)
		ret.push_back(a[i]);
	for (int i = 0; i < (int)b.size(); ++i)
		ret.push_back(b[i]);
	return ret;
}

vector<int64> factor(int64 n) {
	if (n <= 1)
		return vector<int64>();
	if (is_prime(n))
		return vector<int64>(1, n);
	int64 p = n;
	while (p >= n)
		p = pollard_rho(n, rand() % (n - 1) + 1);
	return merge(factor(n / p), factor(p));
}

