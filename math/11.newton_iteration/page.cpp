//use newton-method to solve f(x) = 0
//init x0
//xi -> x(i + 1) = xi - f(xi) / f'(xi)
//O(N^2logN)
int64 square_root(int64 x) {
	if (x <= 0)
		return 0;
	int64 last_root = -1, root = 1 << (bit_length(x) / 2);
	while (true) {
		int64 next_root = (root + x / root) >> 1;
		if (next_root == last_root)
			return min(next_root, root);
		last_root = root;
		root = next_root;
	}
}

