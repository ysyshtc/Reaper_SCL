#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
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
		null_space = vector<vector<double> >(dimension, vector<double>(size, 0));
	}
};

solution gauss_elimination(vector<vector<double> > a, vector<double> b) {
	int n = (int)a.size(), m = (int)a[0].size();
	int index[n], row = 0;
	bool pivot[m];
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
				ret.null_space[cnt][index[j]] = a[j][i];
			ret.null_space[cnt++][i] = -1;
		}
	return ret;
}

int main() {
	int n, m;
	double tmp;
	scanf("%d %d", &n, &m);
	vector<vector<double> > a(n, vector<double>());
	vector<double> b;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			scanf("%lf", &tmp);
			a[i].push_back(tmp);
		}
		scanf("%lf", &tmp);
		b.push_back(tmp);
	}
	solution sol = gauss_elimination(a, b);
	if (sol.size == 0) {
		puts("no solution!");
		return 0;
	}

	for (int i = 0; i < m; ++i)
		printf("%.4f ", sol.special[i]);
	puts("");
	for (int i = 0; i < sol.dimension; ++i) {
		for (int j = 0; j < m; ++j)
			printf("%.4f ", sol.null_space[i][j]);
		puts("");
	}
}
