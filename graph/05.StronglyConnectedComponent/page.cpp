int n, dfn[N], stack[N], top, low[N], ord, cnt, ans, color[N];
vector<int> E[N];
bool instack[N], inEdge[N];
void trajan(int i) {
	dfn[i] = low[i] = ++ord;
	stack[++top] = i;
	instack[i] = true;
	for (int j = 0; j < (int) E[i].size(); j++) {
	if (!dfn[E[i][j]]) {
		trajan(E[i][j]);
		low[i] = min(low[i], low[E[i][j]]);
	}
	else if (instack[E[i][j]])
		low[i] = min(low[i], dfn[E[i][j]]);
	}
	
	if (dfn[i] == low[i])
	for (cnt++; ; ) {
		int j = stack[top--];
		color[j] = cnt;
		instack[j] = false;
		if (j == i) break;
	}
}
int main() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) trajan(i);
	for (int i = 1; i <= n; i++) 
	for (int j = 0; j < (int) E[i].size(); j++)
	if (color[E[i][j]] != color[i]) addEdge(color[E[i][j]], color[i]);
}

