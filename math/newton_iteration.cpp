#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

//use newton-method to solve f(x) = 0
//init x0
//xi -> x(i + 1) = xi - f(xi) / f'(xi)

int bit_length(ll x) {
	int ret = 0;
	for (; x > 1; x >>= 1) ++ret;
	return ret;
}

//O(N^2logN)
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

int main() {
	ll n;
	cin >> n;
	cout << square_root(n) << endl;
}
