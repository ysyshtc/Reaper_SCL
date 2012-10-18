const int MAXN = 200,  MAXM = 100000, inf = 1 << 25;
int n, m, f[MAXN], p[MAXM], t[MAXM], c[MAXM], ord[MAXM], ori[MAXM], g[MAXN];
int top, in[MAXN], X, Y, S, T, total, head, tail, Q[MAXN], d[MAXN];
void addE(int a, int b, int low, int high) {
	p[++top] = b; c[top] = high - low;
	t[top] = f[a]; f[a] = top;
	p[++top] = a; c[top] = 0;
	t[top] = f[b]; f[b] = top;
	in[a] -= low; in[b] += low;
}
int dinic();
int main() {
	for (; scanf("%d%d", &n, &m) == 2; ) {
		X = 1; Y = n; S = 0; T = n + 1; top = 1; total = 0;
		memset(f, 255, sizeof(f));
		memset(in,  0, sizeof(in));
		for (int i = 1; i <= m; i++) {
			int u, v, z, c;
			scanf("%d%d%d%d", &u, &v, &z, &c);
			ori[i] = z; ord[i] = top + 1;
			if (c) addE(u, v, z, z);
			else addE(u, v, 0, z);
		}
		for (int i = X; i <= Y; i++)
		if (in[i] > 0)
			addE(S, i, 0, in[i]);
		else {
			addE(i, T, 0,-in[i]);
			total -= in[i];
		}
		int flow1 = dinic();
		int now = top + 1;
		addE(Y, X, 0, inf);
		int flow2 = dinic();
		if (flow1 + flow2 != total)
		puts("Impossible");
		else {
			printf("%d\n", c[now ^ 1]);
			for (int i = 1; i <= m; i++)
			printf("%d%c", ori[i] - c[ord[i]], i == m ? '\n' : ' ');
		}
	}
}

bool bfs(int S, int T) {
	memset(d, 0, sizeof(d));
	head = tail = 0;
	d[Q[tail++] = S] = 1;
	for (; head < tail; )
	for (int i = Q[head++], j = g[i] = f[i]; j != -1; j = t[j]) 
	if (c[j] && !d[p[j]]) {
		d[p[j]] = d[i] + 1;
		Q[tail++] = p[j];
	}
	return d[T];
}
int dfs(int i, int flow) {
	if (i == T) return flow;
	int ans = 0, tmp;
	for (int j = g[i]; j != -1; j = g[i] = t[j]) 
	if (c[j] && d[p[j]] == d[i] + 1) {
		tmp = dfs(p[j], min(flow, c[j]));
		flow -= tmp; ans += tmp;
		c[j] -= tmp; c[j ^ 1] += tmp;
		if (!flow) return ans;
	}
	return ans;
}
int dinic() {
	int ans = 0;
	while (bfs(S, T)) ans += dfs(S, inf);
	return ans;
}

