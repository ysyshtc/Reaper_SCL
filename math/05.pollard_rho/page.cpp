int64 pollard_rho(int64 n, int64 c) {
	int64 x = rand() % (n - 1) + 1, y = x;
	for (int head = 1, tail = 2; true; ) {
		x = multiply_mod(x, x, n);
		if ((x += c) >= n)
			x -= n;
		if (x == y)
			return n;
		int64 d = gcd(my_abs(x - y), n);
		if (d > 1 && d < n)
			return d;
		if ((++head) == tail) {
			y = x;
			tail <<= 1;
		}
	}
}

