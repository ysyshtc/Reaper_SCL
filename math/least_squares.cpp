#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-7;

vector<double> operator* (const vector<double> &a, double b) {
	vector<double> ret;
	for (int i = 0; i < (int)a.size(); ++i)
		ret.push_back(a[i] * b);
	return ret;
}

vector<double> operator+ (const vector<double> &a, const vector<double> &b) {
	vector<double> ret;
	for (int i = 0; i < (int)a.size(); ++i)
		ret.push_back(a[i] + b[i]);
	return ret;
}

vector<double> operator- (const vector<double> &a, const vector<double> &b) {
	vector<double> ret;
	for (int i = 0; i < (int)a.size(); ++i)
		ret.push_back(a[i] - b[i]);
	return ret;
}

struct solution {
	int size, dimension;
	vector<vector<double> > null_space;
	vector<double> special;
	solution(int size = 0, int dimension = 0) : size(size), dimension(dimension) {
		special = vector<double>(size, 0);
		null_space = vector<vector<double> >(size, vector<double>(dimension, 0));
	}
};

solution gauss_elimination(vector<vector<double> > a, vector<double> b) {
	int n = (int)a.size(), m = (int)a[0].size();
	static const int MAX_SIZE = 211;
	int index[MAX_SIZE], row = 0;
	bool pivot[MAX_SIZE];
	fill(index, index + n, -1);
	fill(pivot, pivot + m, false);

	for (int col = 0; row < n && col < m; ++col) {
		int best = row;
		for (int i = row + 1; i < n; ++i)
			if (fabs(a[i][col]) > fabs(a[best][col]))
				best = i;
		swap(a[best], a[row]);
		swap(b[best], b[row]);
		if (fabs(a[row][col]) < EPS)
			continue;
		pivot[col] = true;
		index[row] = col;
		double coef = a[row][col];
		a[row] = a[row] * (1. / coef);
		b[row] = b[row] * (1. / coef);
		for (int i = 0; i < n; ++i)
			if (i != row && fabs(a[i][col]) > EPS) {
				double coef = a[i][col];
				a[i] = a[i] - a[row] * coef;
				b[i] = b[i] - b[row] * coef;
			}
		++row;
	}

	for (int i = row; i < n; ++i)
		if (fabs(b[i]) > EPS)
			return solution(0, 0);					//no solution

	solution ret(m, m - row);
	for (int i = 0; i < row; ++i)
		ret.special[index[i]] = b[i];

	int cnt = 0;
	for (int i = 0; i < m; ++i)
		if (!pivot[i]) {
			for (int j = 0; j < row; ++j)
				ret.null_space[index[j]][cnt] = a[j][i];
			ret.null_space[i][cnt++] = -1;
		}
	return ret;
}

// calculate argmin ||AX - B||
solution least_squares(vector<vector<double> > a, vector<double> b) {
	int n = (int)a.size(), m = (int)a[0].size();
	vector<vector<double> > p(m, vector<double>(m, 0));
	vector<double> q(m, 0);
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			for (int k = 0; k < n; ++k)
				p[i][j] += a[k][i] * a[k][j];
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			q[i] += a[j][i] * b[j];
	return gauss_elimination(p, q);
}

void print(const vector<double> &p) {
	int n = (int)p.size();
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += p[i] * p[i];
		if (i == n - 1)
			printf("%.5f\n", p[i]);
		else
			printf("%.5f ", p[i]);
	}
}

vector<double> my_negate(const vector<double> &v) {
	vector<double> ret;
	for (int i = 0; i < (int)v.size(); ++i)
		ret.push_back(-v[i]);
	return ret;
}

int main() {
	int n, m;
	double tmp;
	scanf("%d %d", &n, &m);
	vector<vector<double> > a(n, vector<double>());
	vector<double> b;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%lf", &tmp);
			a[j].push_back(tmp);
		}
	}
	for (int i = 0; i < n; ++i) {
		scanf("%lf", &tmp);
		b.push_back(tmp);
	}
	solution sol = least_squares(a, b);
	if (sol.dimension == 0)
		print(sol.special);
	else {
		solution val = least_squares(sol.null_space, my_negate(sol.special));
		vector<double> ans = sol.special;
		for (int i = 0; i < sol.dimension; ++i)
			for (int j = 0; j < sol.null_space.size(); ++j)
				ans[j] += sol.null_space[j][i] * val.special[i];
		print(ans);
	}
}
