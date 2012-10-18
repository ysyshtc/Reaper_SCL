const int oo = 0x7fffffff;
int n, w[N][N], x[N], y[N], px[N], py[N], sy[N], slack[N], par[N];
void adjust(int v) { sy[v] = py[v];  if (px[sy[v]] != -2) adjust(px[sy[v]]);  }
bool find(int v) {
	for (int i = 0; i < n; i++) if (py[i] == -1) {
		if (slack[i] > x[v] + y[i] - w[v][i]) {
			slack[i] = x[v] + y[i] - w[v][i];
			par[i] = v;
		}
		if (x[v] + y[i] == w[v][i]) {
			py[i] = v;
			if (sy[i] == -1) {
				adjust(i);
				return true;
			}
			if (px[sy[i]] != -1) continue;
			px[sy[i]] = i;
			if (find(sy[i])) return true;
		}
	}
	return false;
}

int km() {
	int i, j, m;
	for (i = 0; i < n; i++) sy[i] = -1, y[i] = 0;
	for (i = 0; i < n; i++) for (x[i] = j = 0; j < n; j++) x[i] = max(x[i], w[i][j]);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) px[j] = py[j] =  - 1, slack[j] = oo;
		px[i] = -2;
		if (find(i)) continue;
		bool flag = false;
		for (; !flag; ) {
			m = oo;
			for (j = 0; j < n; j++) if (py[j]== -1) m = min(m, slack[j]);
			for (j = 0; j < n; j++) {
				if (px[j] != -1) x[j] -= m;
				if (py[j] != -1) y[j] += m;
				else slack[j] -= m;
			}
			for (j = 0; j < n; j++) {
				if (py[j]== -1 && !slack[j]) {
					py[j] = par[j];
					if (sy[j]== -1) {
						adjust(j);
						flag = true;
						break;
					}
					px[sy[j]] = j;
					if (find(sy[j])) {
						flag = true;
						break;
					}
				}
			}
		}
	}
	int ans = 0;
	for (i = 0; i < n; i++) ans += w[sy[i]][i];
	return ans;
}

