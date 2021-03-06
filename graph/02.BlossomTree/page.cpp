const int N = 240;
int n, Next[N], f[N], mark[N], visited[N], Link[N], Q[N], head, tail;
vector<int> E[N];
int getf(int x) { return f[x] == x ? x : f[x] = getf(f[x]); }
void merge(int x, int y) { x = getf(x); y = getf(y); if (x != y) f[x] = y; }
int LCA(int x, int y) {
	static int flag = 0;
	flag++;
	for (; ; swap(x, y)) if (x != -1) {
		x = getf(x);
		if (visited[x] == flag) return x;
		visited[x] = flag;
		if (Link[x] != -1) x = Next[Link[x]];
		else x = -1;
	}
}
void go(int a, int p) {
	while (a != p) {
		int b = Link[a], c = Next[b];
		if (getf(c) != p) Next[c] = b;
		if (mark[b] == 2) mark[Q[tail++] = b] = 1;
		if (mark[c] == 2) mark[Q[tail++] = c] = 1;
		merge(a, b); merge(b, c); a = c;
	}
}
void find(int s) {
	for (int i = 0; i < n; i++) {
		Next[i] = -1; f[i] = i;
		mark[i] = 0; visited[i] = -1;
	}
	head = tail = 0; Q[tail++] = s; mark[s] = 1;
	for (; head < tail && Link[s] == -1; )
	for (int i = 0, x = Q[head++]; i < (int) E[x].size(); i++)
	if (Link[x] != E[x][i] && getf(x) != getf(E[x][i]) && mark[E[x][i]] != 2) {
		int y = E[x][i];
		if (mark[y] == 1) {
			int p = LCA(x, y);
			if (getf(x) != p) Next[x] = y;
			if (getf(y) != p) Next[y] = x;
			go(x, p);
			go(y, p);
		}
		else if (Link[y] == -1) {
			Next[y] = x;
			for (int j = y; j != -1; ) {
				int k = Next[j];
				int tmp = Link[k];
				Link[j] = k;
				Link[k] = j;
				j = tmp;
			}
			break;
		}
		else {
			Next[y] = x;
			mark[Q[tail++] = Link[y]] = 1;
			mark[y] = 2;
		}
	}
}
int main() {
	for (int i = 0; i < n; i++) Link[i] = -1;
	for (int i = 0; i < n; i++) if (Link[i] == -1) find(i);
	int ans = 0;
	for (int i = 0; i < n; i++) ans += Link[i] != -1;
}

