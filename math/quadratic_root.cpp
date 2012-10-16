#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

int t, x, p;

inline int pow_mod(int x, int y, int p) {
	int cur = x, ret = 1;
	while (y > 0) {
		if (y & 1)
			ret = ret * cur % p;
		cur = cur * cur % p;
		y /= 2;
	}
	return ret;
}

inline bool quad_resi(int x, int p) {
	return pow_mod(x, (p - 1) / 2, p) == 1;
}

struct quad_poly {
	int zero, one, val, mod;

	quad_poly(int zero, int one, int val, int mod) : zero(zero), one(one), val(val), mod(mod) {}

	quad_poly multiply(quad_poly o) {
		int z0 = (zero * o.zero + one * o.one % mod * val % mod) % mod;
		int z1 = (zero * o.one + one * o.zero) % mod;
		return quad_poly(z0, z1, val, mod);
	}

	quad_poly pow(int x) {
		if (x == 1)
			return *this;
		quad_poly ret = this->pow(x / 2);
		ret = ret.multiply(ret);
		if (x & 1)
			ret = ret.multiply(*this);
		return ret;
	}
};

inline int sqr(int x) { return x * x; }

inline int calc(int a, int p) {
	if (a < 2)
		return a;
	if (!quad_resi(a, p))
		return p;
	if (p % 4 == 3)
		return pow_mod(a, (p + 1) / 4, p);
	int b = 0;
	while (quad_resi((sqr(b) - a + p) % p, p))
		b = rand() % p;
	quad_poly ret = quad_poly(b, 1, (sqr(b) - a + p) % p, p);
	ret = ret.pow((p + 1) / 2);
	return ret.zero;
}

int main() {
	for (scanf("%d", &t); t-- > 0; ) {
		scanf("%d %d", &x, &p);
		x %= p;
		int ans = calc(x, p);
		if (ans == p)
			puts("No root");
		else {
			if (ans == 0 || p == 2)
				printf("%d\n", ans);
			else {
				if (ans > p - ans)
					ans = p - ans;
				printf("%d %d\n", ans, p - ans);
			}
		}
	}
	return 0;
}
