int n, m, f[N], fa[N], l[N], ans1, ans2, h[N];
vector<pair<int, pair<int, int> > > e;
vector<pair<int, int> > E[N];
bool b[M];
int F(int x) { return f[x] == x ? x : f[x] = F(f[x]); }
bool merge(int a, int b, int c) {
	int A = F(a), B = F(b);
	if (A != B) {
		f[A] = B;
		E[a].push_back(make_pair(b, c));
		E[b].push_back(make_pair(a, c));
		ans1 += c;
	}
	return A != B;
}
void dfs(int i, int FA, int H) {
	fa[i] = FA; h[i] = H;
	for (int j = 0; j < (int) E[i].size(); j++)
	if (E[i][j].first != FA) {
		l[E[i][j].first] = E[i][j].second;
		dfs(E[i][j].first, i, H + 1);
	}
}
int main() {
	sort(e.begin(), e.end());
	for (int i = 1; i <= n; i++) f[i] = i;
	for (int i = 0; i < m; i++)
		b[i] = merge(e[i].second.first, e[i].second.second, e[i].first);
	dfs(1, -1, 1);
	ans2 = (int) 1e9;
	for (int i = 1; i <= n; i++) f[i] = i;
	for (int i = 0; i < m; i++)
	if (!b[i]) {
		int a = F(e[i].second.first), b = F(e[i].second.second), c = e[i].first;
		for (; a != b;) {
			if (h[a] > h[b]) swap(a, b);
			if (h[a] < h[b]) {
				ans2 = min(ans2, c - l[b]);
				f[b] = fa[b];
				b = F(b);
			} else {
				ans2 = min(ans2, c - max(l[a], l[b]));
				f[a] = fa[a];
				f[b] = fa[b];
				a = F(a);
				b = F(b);
			}
		}
	}
}

