const int MAXD = 20;
int a[MAXN], b[MAXN], t[MAXD][MAXN], p[MAXD][MAXN], n, m, u, v, k;
void calc(int dep, int l, int r) {
	if (l == r - 1) return;
	int mid = (l + r + 1) / 2, k = b[mid - 1], n1 = l, n2 = mid;
	for (int i = l; i < r; ++i)
		if (t[dep][i] <= k && n1 < mid)
			t[dep + 1][n1++] = t[dep][i], ++p[dep][i];
		else
			t[dep + 1][n2++] = t[dep][i];
	for (int i = l + 1; i < r; ++i)
		p[dep][i] += p[dep][i - 1];
	calc(dep + 1, l, mid);
	calc(dep + 1, mid, r);
}
int query(int dep, int l, int r, int u, int v, int k) {
	if (l == r - 1)
		return t[dep][l];
	int c = u!=l ? p[dep][u-1] : 0,d = p[dep][v-1],mid = (l+r+1)/2;
	if (d - c >= k)
		return query(dep+1, l, mid, l+c, l+d, k);
	else
		return query(dep+1, mid, r, u-l-c+mid, v-l-d+mid, k-d+c);
}
int main(int argc, char* argv[]) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	memcpy(b, a, sizeof a);
	sort(b, b + n);
	memcpy(t[0], a, sizeof a);
	calc(0, 0, n);
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &u, &v, &k);
		printf("%d\n", query(0, 0, n, u - 1, v, k));
	}
}

