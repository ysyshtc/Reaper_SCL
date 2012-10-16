#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

ll multiply_mod(ll x, ll y, ll mod) {
	ll ret = 0, val = x % mod;
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

ll pow_mod(ll x, ll y, ll mod) {
	ll ret = 1, val = x;
	for (; y > 0; y >>= 1) {
		if ((y & 1) == 1)
			ret = multiply_mod(ret, val, mod);
		val = multiply_mod(val, val, mod);
	}
	return ret;
}

bool test(ll n, int base) {
	ll m = n - 1, ret = 0;
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

ll special[7] = {
	1373653LL,
	25326001LL,
	3215031751LL,
	25000000000LL,
	2152302898747LL,
	3474749660383LL,
	341550071728321LL
};

bool is_prime(ll n) {
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

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll my_abs(ll a) { return a < 0 ? -a : a; }

ll pollard_rho(ll n, ll c) {
	ll x = rand() % (n - 1) + 1, y = x;
	for (ll head = 1, tail = 2; true; ) {
		x = multiply_mod(x, x, n);
		if ((x += c) >= n)
			x -= n;
		if (x == y)
			return n;
		ll d = gcd(my_abs(x - y), n);
		if (d > 1 && d < n)
			return d;
		if ((++head) == tail) {
			y = x;
			tail <<= 1;
		}
	}
}

vector<ll> merge(const vector<ll> &a, const vector<ll> &b) {
	vector<ll> ret;
	for (int i = 0; i < (int)a.size(); ++i)
		ret.push_back(a[i]);
	for (int i = 0; i < (int)b.size(); ++i)
		ret.push_back(b[i]);
	return ret;
}

vector<ll> factor(ll n) {
	if (n <= 1)
		return vector<ll>();
	if (is_prime(n))
		return vector<ll>(1, n);
	ll p = n;
	while (p >= n)
		p = pollard_rho(n, rand() % (n - 1) + 1);
	return merge(factor(n / p), factor(p));
}

int main() {
	int task_count;
	cin >> task_count;
	for (int i = 0; i < task_count; ++i) {
		ll n;
		cin >> n;
		vector<ll> ans = factor(n);
		if ((int)ans.size() == 1)
			cout << "Prime" << endl;
		else {
			sort(ans.begin(), ans.end());
			cout << ans[0] << endl;
		}
	}
}
