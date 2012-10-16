int crt_merge(vector<int> divide, vector<int> remainder) {
	int n = 1, ret = 0;
	for (int i = 0; i < (int)divide.size(); ++i)
		n *= divide[i];
	for (int i = 0; i < (int)remainder.size(); ++i) {
		int m = n / divide[i];
		ret = (ret + (int64)m * remainder[i] % n * inverse(m, divide[i])) % n;
	}
	return ret;
}

