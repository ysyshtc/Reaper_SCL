#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>

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

ll crt_merge(vector<int> divide, vector<int> remainder) {
	ll n = 1, ret = 0;
	for (int i = 0; i < (int)divide.size(); ++i)
		n *= divide[i];
	for (int i = 0; i < (int)remainder.size(); ++i) {
		ll m = n / divide[i];
		ret = (ret + m * remainder[i] % n * inv_mod(m, divide[i])) % n;
	}
	return ret;
}

int main() {
	vector<int> a;
	vector<int> b;
	a.push_back(2);
	a.push_back(3);
	a.push_back(5);
	a.push_back(7);

	b.push_back(0);
	b.push_back(1);
	b.push_back(4);
	b.push_back(5);

	cout << crt_merge(a, b) << endl;
}
