#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>
#include <set>

using namespace std;

const int mod = (15 << 27) + 1;
const int g = 31;

vector<int> nth_root;

void transform(vector<int>& a, bool inverse) {
	int n = (int)a.size();
	vector<int> leaf;
	leaf.push_back(0);
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < i; ++j)
			leaf[j + i] = (leaf[j] <<= 1) + 1;
	vector<int> tmp(a);
	for (int i = 0; i < n; ++i)
		a[i] = tmp[leaf[i]];

	for (int step = 1; step < n; step <<= 1) {
		for (int start = 0; start < n; start += step << 1) {
			for (int i = 0; i < step; ++i) {
				long long root = nth_root[(inverse ? n - i * n / 2 / step : i * n / 2 / step) % n];
				long long l = a[start + i], r = root * a[start + step + i] % mod;
				a[start + i] = (l + r) % mod;
				a[start + i + step] = (l - r + mod) % mod;
			}
		}
	}
}

inline int low_bit(int x) { return -x & x; }

vector<int> dot(const vector<int>& a, const vector<int>& b) {
	vector<int> ret;
	int n = (int)a.size();
	for (int i = 0; i < n; ++i)
		ret.push_back((long long)a[i] * b[i] % mod);
	return ret;
}

int pow(int x, int y, int mod) {
	if (y == 0)
		return 1;
	int ret = pow(x, y / 2, mod);
	ret = (long long)ret * ret % mod;
	if (y & 1)
		ret = (long long)ret * x % mod;
	return ret;
}

vector<int> multiply(vector<int> u, vector<int> v) {
	int n = u.size() + (int)v.size() - 1;
	while (low_bit(n) != n)
		n += low_bit(n);
	for (int i = (int)u.size(); i < n; ++i)
		u.push_back(0);
	for (int i = (int)v.size(); i < n; ++i)
		v.push_back(0);

	nth_root.clear();
	int r = pow(g, (mod - 1) / n, mod);
	for (int i = 0, tmp = 1; i < n; ++i) {
		nth_root.push_back(tmp);
		tmp = (long long)tmp * r % mod;
	}

	transform(u, false);
	transform(v, false);

	vector<int> ret = dot(u, v);
	int inv = pow(n, mod - 2, mod);
	for (int i = 0; i < n; ++i)
		ret[i] = (long long)ret[i] * inv % mod;
	transform(ret, true);
	return ret;
}

inline vector<int> next_vector() {
	string s;
	cin >> s;
	vector<int> ret;
	for (int i = 0; i < (int)s.length(); ++i)
		ret.push_back(s[i] - '0');
	reverse(ret.begin(), ret.end());
	return ret;
}

int main() {
	vector<int> u = next_vector();
	vector<int> v = next_vector();

	vector<int> ans = multiply(u, v);
	for (int i = 0; i < 10; ++i)
		ans.push_back(0);

	for (int i = 0; i < (int)ans.size() - 1; ++i)
		if (ans[i] >= 10) {
			ans[i + 1] += ans[i] / 10;
			ans[i] %= 10;
		}
	while ((int)ans.size() > 1 && ans.back() == 0)
		ans.pop_back();
	
	for (int i = (int)ans.size() - 1; i >= 0; --i)
		cout << ans[i];
	cout << endl;
}
