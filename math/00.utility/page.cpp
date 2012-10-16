typedef long long int64;
int64 gcd(int64 a, int64 b) { return b ? gcd(b, a % b) : a; }
int64 my_abs(int64 x) { return x < 0 ? -x : x; }
int64 my_sqr(int64 x) { return x * x; }
inline int low_bit(int x) { return -x & x; }

int64 multiply_mod(int64 x, int64 y, int64 mod) {
	int64 ret = 0, val = x % mod;
	for (; y > 0; y >>= 1) {
		if ((y & 1) == 1) {
			if ((ret += val) >= mod)
				ret -= mod;
		}
		if ((val += val) >= mod)
			val -= mod;
	}
	return ret;
}

int64 pow_mod(int64 x, int64 y, int64 mod) {
	int64 ret = 1, val = x;
	for (; y > 0; y >>= 1) {
		if ((y & 1) == 1)
			ret = multiply_mod(ret, val, mod);
		val = multiply_mod(val, val, mod);
	}
	return ret;
}

int bit_length(int64 x) {
	int ret = 0;
	for (; x > 1; x >>= 1) ++ret;
	return ret;
}

