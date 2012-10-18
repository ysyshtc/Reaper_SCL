const int MAX_N = 444;//take care, MAX_N being the size of X add Y
int n, m;
vector<int> E[MAX_N];
int match[MAX_N], d[MAX_N];
bool bfs() {
	static int que[MAX_N], r;
	fill(d + 1, d + 1 + n + m, 0);
	r = 0;
	for (int i = 1; i <= n; ++i)
		if (!match[i])
			que[r++] = i;
	bool ret = false;
	for (int i = 0; i < r; ++i) {
		int x = que[i];
		if (x > n) {
			d[que[r++] = match[x]] = d[x] + 1;
		} else {
			for (vector<int>::iterator e = E[x].begin(); e != E[x].end(); ++e)
				if (!d[*e]) {
					d[*e] = d[x] + 1;
					if (!match[*e])
						ret = true;
					else
						que[r++] = *e;
				}
		}
	}
	return ret;
}
bool find(int x) {
	for (vector<int>::iterator e = E[x].begin(); e != E[x].end(); ++e)
		if (d[x] + 1 == d[*e]) {
			d[*e] = -1;
			if (!match[*e] || find(match[*e])) {
				match[x] = *e, match[*e] = x;
				return true;
			}
		}
	return false;
}
int main() {
	fill(match + 1, match + 1 + n + m, 0);
	int result = 0;
	while (bfs())
		for (int i = 1; i <= n; ++i)
			if (!match[i])
				result += find(i);
}

