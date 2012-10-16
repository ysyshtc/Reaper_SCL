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

template<typename data_type>
struct Complex {
	data_type x, y;
	Complex(data_type x = data_type(), data_type y = data_type()) : x(x), y(y) {};
	const data_type& real() const { return x; }
	const data_type& imag() const { return y; }
	Complex operator+ (const Complex& o) const {
		return Complex(real() + o.real(), imag() + o.imag());
	}
	Complex operator* (const Complex& o) const {
		return Complex(real() * o.real() - imag() * o.imag(), real() * o.imag() + imag() * o.real());
	}
	Complex operator- (const Complex& o) const {
		return Complex(real() - o.real(), imag() - o.imag());
	}
	Complex operator/ (const data_type& o) const {
		return Complex(real() / o, imag() / o);
	}
	data_type norm() const {
		return real() * real() + imag() * imag();
	}
	Complex conj() const {
		return Complex(real(), -imag());
	}
	void out() {
		cout << real() << "+" << imag() << "i" << endl;
	}
};

typedef vector<Complex<double> > VCD;

const double PI = acos(-1.0);
const double EPS = 1e-8;

VCD nth_root;

void transform(VCD& a, bool inverse) {
	int n = (int)a.size();
	for (int step = n / 2; step > 0; step >>= 1) {
		for (int start = 0; start < step; ++start) {
			VCD ret;
			int m = n / step;
			for (int i = 0; i < m; ++i) {
				Complex<double> root = nth_root[i * step];
				if (inverse)
					root = root.conj();
				int index = (i < m / 2 ? i : i - m / 2) * 2 * step;
				ret.push_back(a[start + index] + root * a[start + step + index]);
			}
			for (int i = 0; i < m; ++i)
				a[start + i * step] = ret[i];
		}
	}
}

inline int low_bit(int x) { return -x & x; }

VCD dot(const VCD& a, const VCD& b) {
	VCD ret;
	int n = (int)a.size();
	for (int i = 0; i < n; ++i)
		ret.push_back(a[i] * b[i]);
	return ret;
}

VCD multiply(VCD u, VCD v) {
	int n = u.size() + (int)v.size() - 1;
	while (low_bit(n) != n)
		n += low_bit(n);
	for (int i = (int)u.size(); i < n; ++i)
		u.push_back(Complex<double>());
	for (int i = (int)v.size(); i < n; ++i)
		v.push_back(Complex<double>());
	nth_root.clear();
	for (int i = 0; i < n; ++i) {
		double theta = 2 * PI * i / n;
		nth_root.push_back(Complex<double>(cos(theta), sin(theta)));
	}

	transform(u, false);
	transform(v, false);

	VCD ret = dot(u, v);
	for (int i = 0; i < n; ++i)
		ret[i] = ret[i] / n;
	transform(ret, true);
	return ret;
}

inline VCD next_vector() {
	string s;
	cin >> s;
	VCD ret;
	for (int i = 0; i < (int)s.length(); ++i)
		ret.push_back(Complex<double>(s[i] - '0', 0));
	reverse(ret.begin(), ret.end());
	return ret;
}

int main() {
	VCD u = next_vector();
	VCD v = next_vector();

	VCD ret = multiply(u, v);
	vector<int> ans;
	for (int i = 0; i < (int)ret.size(); ++i)
		ans.push_back((int)(ret[i].real() + EPS));
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
