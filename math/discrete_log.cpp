#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <map>
#include <cstring>

using namespace std;

typedef long long ll;

ll pow_mod(ll x, ll y, ll mod) {
	ll ret = 1, val = x % mod;
	for (; y > 0; y >>= 1) {
		if ((y & 1) == 1)
			ret = ret * val % mod;
		val = val * val % mod;
	}
	return ret;
}

ll inv_mod(ll m, ll n) {
	return pow_mod(m, n - 2, n);
}

struct hash_table {
	static const int MAXN = 100003;
	int first[MAXN], key[MAXN], value[MAXN], next[MAXN], tot;
	hash_table() : tot(0) {
		memset(first, 255, sizeof first);
	}
	void clear() {
		memset(first, 255, sizeof first);
		tot = 0;
	}
	int &operator[] (const int &o) {
		int pos = o % MAXN;
		for (int i = first[pos]; i != -1; i = next[i])
			if (key[i] == o)
				return value[i];
		next[tot] = first[pos];
		first[pos] = tot;
		key[tot] = o;
		return value[tot++];
	}
	bool has_key(const int &o) {
		int pos = o % MAXN;
		for (int i = first[pos]; i != -1; i = next[i])
			if (key[i] == o)
				return true;
		return false;
	}
};

int discrete_log(int base, int n, int mod) {
	int block = int(sqrt(mod)) + 1;
	int val = 1;
	hash_table dict;
	for (int i = 0; i < block; ++i) {
		if (dict.has_key(val) == 0)
			dict[val] = i;
		val = (ll)val * base % mod;
	}
	int inv = inv_mod(val, mod);
	val = 1;
	for (int i = 0; i < block; ++i) {
		if (dict.has_key((ll)val * n % mod))
			return dict[(ll)val * n % mod] + i * block;
		val = (ll)val * inv % mod;
	}
	return -1;
}

int main() {
	int base, n, p;
	while (scanf("%d %d %d", &p, &base, &n) == 3) {
		int ans = discrete_log(base, n, p);
		if (ans == -1)
			puts("no solution");
		else
			printf("%d\n", ans);
	}
}
