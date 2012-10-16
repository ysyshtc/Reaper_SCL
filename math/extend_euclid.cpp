#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

ll extend_euclid(ll a, ll b, ll &m, ll &n) {
	if (b == 0) {
		m = 1; n = 0;
		return a;
	}
	ll ret = extend_euclid(b, a % b, n, m);
	n -= a / b * m;
	return ret;
}

int main() {
	ll a, b;
	extend_euclid(20, 290, a, b);
	cout << a << " " << b << endl;
}
