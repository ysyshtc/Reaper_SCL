vector<int> E[1005];
bool v[1005], M[1005][1005];
int n, m, label[1005], ans[1005], num[1005];
int main() {
	for (; scanf("%d%d", &n, &m) == 2 && (n || m); ) {
		for (int i = 1; i <= n; i++) label[i] = ans[i] = 0, v[i] = false, E[i].clear();
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) M[i][j] = false;
		for (; m--; ) {
			int x, y; scanf("%d%d", &x, &y);
			E[x].push_back(y); E[y].push_back(x);
			M[x][y] = M[y][x] = true;
		}
		for (int now = n; now >= 1; now--) {
			int k = -1;
			for (int i = 1; i <= n; i++)
			if (!v[i] && (k == -1 || label[i] > label[k])) k = i;
			ans[now] = k; num[k] = now; v[k] = true;
			for (int i = 0; i < (int) E[k].size(); i++)
			if (!v[E[k][i]]) label[E[k][i]]++;
		}
		bool ok = true;
		for (int i = 1; i <= n && ok; i++) {
			int k = -1;
			for (int j = 0; j < (int) E[ans[i]].size(); j++)
			if (num[E[ans[i]][j]] > i && (k == -1 || num[E[ans[i]][j]] < num[k])) k = E[ans[i]][j];
			for (int j = 0; j < (int) E[ans[i]].size(); j++)
			if (num[E[ans[i]][j]] > i && !M[k][E[ans[i]][j]] && k != E[ans[i]][j]) {
				ok = false; break;
			}
		}
		if (ok) puts("Perfect"); else puts("Imperfect");puts("");
	}
}

