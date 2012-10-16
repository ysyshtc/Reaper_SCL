#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

typedef long long ll;

int bit_length(ll x) {
	int ret = 0;
	for (; x > 1; x >>= 1) ++ret;
	return ret;
}

ll square_root(ll x) {
	if (x <= 0)
		return 0;
	ll last_root = -1, root = 1 << (bit_length(x) / 2);
	while (true) {
		ll next_root = (root + x / root) >> 1;
		if (next_root == last_root)
			return min(next_root, root);
		last_root = root;
		root = next_root;
	}
}

vector<ll> solve_pell(ll n) {
	const static int MAXC = 1111;
	ll p[MAXC], q[MAXC], a[MAXC], g[MAXC], h[MAXC];
	p[1] = 1; p[0] = 0;
	q[1] = 0; q[0] = 1;
	a[2] = square_root(n);
	g[1] = 0; h[1] = 1;
	for (int i = 2; ; ++i) {
		g[i] = -g[i - 1] + a[i] * h[i - 1];
		h[i] = (n - g[i] * g[i]) / h[i - 1];
		a[i + 1] = (g[i] + a[2]) / h[i];
		p[i] = a[i] * p[i - 1] + p[i - 2];
		q[i] = a[i] * q[i - 1] + q[i - 2];
		if (p[i] * p[i] - n * q[i] * q[i] == 1) {
			vector<ll> ret;
			ret.push_back(p[i]);
			ret.push_back(q[i]);
			return ret;
		}
	}
}

int main() {
	ll n;
	cin >> n;
	vector<ll> ret = solve_pell(n);
	cout << ret[0] << " " << ret[1] << endl;
}
