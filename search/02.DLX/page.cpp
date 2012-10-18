//HDU3663 - Power Stations
struct Node {
	int up, dn, lt, rt, col, row;
	void clear() {
		up = dn = lt = rt = col = row = 0;
	}
}grid[1000000];
int cnt[1100], n, m;
void init(int m) {
	for (int i = 1; i <= m + 1; ++i) {
		grid[i].dn = i;
		grid[i].up = i;
		grid[i].col = i;
		grid[i].lt = i - 1;
		grid[i].rt = i + 1;
		cnt[i] = 0;
	}
	grid[1].lt = m + 1;
	grid[m + 1].rt = 1;
}
void remove(int c) {
	grid[grid[c].rt].lt = grid[c].lt;
	grid[grid[c].lt].rt = grid[c].rt;
	for (int t = grid[c].dn; t != c; t = grid[t].dn) {
		for (int tt = grid[t].rt; tt != t; tt = grid[tt].rt) {
			cnt[grid[tt].col]--;
			grid[grid[tt].dn].up = grid[tt].up;
			grid[grid[tt].up].dn = grid[tt].dn;
		}
	}
}
void resume(int c) {
	for (int t = grid[c].up; t != c; t = grid[t].up) {
		for (int tt = grid[t].lt; tt != t; tt = grid[tt].lt) {
			cnt[grid[tt].col]++;
			grid[grid[tt].up].dn = tt;
			grid[grid[tt].dn].up = tt;
		}
	}
	grid[grid[c].rt].lt = c;
	grid[grid[c].lt].rt = c;
}
bool flag;
int tot;
int ta, t1[1100], ans[1100];
int first[1100], last[1100];
void tj(int i, int j) {
	++tot;
	int pre, start;
	if (first[i] == 0)
		first[i] = tot;
	if (last[i] == 0)
		last[i] = tot;
	pre = last[i];
	start = first[i];
	grid[tot].up = grid[j].up;
	grid[grid[j].up].dn = tot;
	grid[tot].dn = j;
	grid[j].up = tot;
	++cnt[j];
	grid[tot].row = i;
	grid[tot].col = j;
	grid[tot].lt = pre;
	grid[pre].rt = tot;
	grid[tot].rt = start;
	grid[start].lt = tot;
	last[i] = tot;
}
int N, M, D;
int L[66], R[66];
int wys[1100][3];
vector<int> E[66];
bool dfs(int k) {
	int i, j;
	if (grid[m + 1].rt == m + 1) {
		ta = k - 1;
		return true;
	}
	int t = m + 1, c = -1;
	for (i = grid[m + 1].rt; i != m + 1; i = grid[i].rt) {
		if (cnt[i] < t) {
			c = i;
			t = cnt[i];
		}
	}
	if (cnt[c] == 0)
		return false;
	remove(c);
	for (i = grid[c].dn; i != c; i = grid[i].dn) {
		for (j = grid[i].rt; j != i; j = grid[j].rt)
			remove(grid[j].col);
		ans[k] = grid[i].row;
		if (dfs(k + 1))
			return true;
		for (j = grid[i].lt; j != i; j = grid[j].lt)
			resume(grid[j].col);
	}
	resume(c);
	return false;
}
bool cmp(int i, int j) {
	return wys[i][0] < wys[j][0];
}
int main() {
	while (scanf("%d%d%d", &N, &M, &D) == 3) {
		m = N + N * D;//n row, m columns
		n = 0;
		for (int i = 1; i <= N; ++i) {
			E[i].clear();
			E[i].push_back(i);
		}
		for (int i = 1; i <= M; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			E[u].push_back(v);
			E[v].push_back(u);
		}
		for (int i = 1; i <= N; ++i) {
			sort(E[i].begin(), E[i].end());
			E[i].erase(unique(E[i].begin(), E[i].end()), E[i].end());
			scanf("%d%d", L + i, R + i);
			int t = R[i] - L[i] + 1;
			n += t * (t + 1) / 2 + 1;
		}
		init(m);
		tot = m + 1;
		for (int i = 1; i <= n; ++i)
			first[i] = last[i] = 0;
		int xxx = 0;
		for (int i = 1; i <= N; ++i) {
			++xxx;
			wys[xxx][0] = i;
			wys[xxx][1] = wys[xxx][2] = 0;
			tj(xxx, i);
			for (int j = L[i]; j <= R[i]; ++j)
				for (int k = j; k <= R[i]; ++k) {
					++xxx;
					wys[xxx][0] = i;
					wys[xxx][1] = j;
					wys[xxx][2] = k;
					tj(xxx, i);
					for (int l = j; l <= k; ++l)
						for (int t = 0; t < (int)E[i].size(); ++t)
							tj(xxx, N + (E[i][t] - 1) * D + l);
				}
		}
		if (dfs(1)) {
			vector<int> v;
			for (int i = 1; i <= ta; ++i)
				v.push_back(ans[i]);
			sort(v.begin(), v.end(), cmp);
			for (int i = 0; i <(int)v.size(); ++i)
				printf("%d %d\n", wys[v[i]][1], wys[v[i]][2]);
			puts("");
		} else {
			puts("No solution\n");
		}
		for (int i = 1; i <= tot; ++i)
			grid[i].clear();
	}
}
