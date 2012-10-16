#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 33333;

vector<int> prim;
bool visited[MAXN];

vector<int> sift(int n) {
	vector<int> ret;
	for (int i = 2; i < n; ++i)
		visited[i] = false;
	for (int i = 2; i < n; ++i)
		if (!visited[i]) {
			ret.push_back(i);
			for (int j = i + i; j < n; j += i)
				visited[j] = true;
		}
	return ret;
}

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
	static const int MAXT = 100003;
	int first[MAXT], key[MAXT], value[MAXT], next[MAXT], tot;
	hash_table() : tot(0) {
		memset(first, 255, sizeof first);
	}
	void clear() {
		memset(first, 255, sizeof first);
		tot = 0;
	}
	int &operator[] (const int &o) {
		int pos = o % MAXT;
		for (int i = first[pos]; i != -1; i = next[i])
			if (key[i] == o)
				return value[i];
		next[tot] = first[pos];
		first[pos] = tot;
		key[tot] = o;
		return value[tot++];
	}
	bool has_key(const int &o) {
		int pos = o % MAXT;
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

ll extend_euclid(ll a, ll b, ll &m, ll &n) {
	if (b == 0) {
		m = 1; n = 0;
		return a;
	}
	ll ret = extend_euclid(b, a % b, n, m);
	n -= a / b * m;
	return ret;
}

vector<int> discrete_root(int expo, int n, int mod) {
	if (n == 0)
		return vector<int>(1, 0);
	int g = primitive_root(mod);
	int e = discrete_log(g, n, mod);
	ll u, v;
	int d = extend_euclid(expo, mod - 1, u, v);
	if (e % d != 0)
		return vector<int>();
	ll delta = (mod - 1) / d;
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

int main() {
	prim = sift(MAXN);
	int p, expo, n;
	scanf("%d %d %d", &p, &expo, &n);
	vector<int> ans = discrete_root(expo, n, p);
	sort(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size());
	for (int i = 0; i < (int)ans.size(); ++i)
		printf("%d\n", ans[i]);
}
