const int MAX_N = 1111111;
int next[MAX_N], len[MAX_N];
int length[2];
char input[2][MAX_N];
void prepare(char *s, int n) {
	next[0] = n;
	for (int &i = next[1] = 0; i < n - 1 && s[i] == s[i + 1]; i++);
	int p = 1;
	for (int i = 2; i < n; ++i) {
		if (p + next[p] - 1 < i) {
			for (int &j = next[i] = 0; i + j < n && s[j] == s[i + j]; j++);
			p = i;
		} else {
			int &j = next[i] = min(next[i - p], p + next[p] - i);
			for (; i + j < n && s[j] == s[i + j]; j++);
			if (i + j > p + next[p])
				p = i;
		}
	}
}
void solve(char *s, int n, char *t, int m) {
	for (int &i = len[0] = 0; i < n && i < m && s[i] == t[i]; i++);
	int p = 0;
	for (int i = 1; i < n; ++i) {
		if (p + len[p] - 1 < i) {
			for (int &j = len[i] = 0; i + j < n && j < m && s[i + j] == t[j]; j++);
			p = i;
		} else {
			int &j = len[i] = min(next[i - p], p + len[p] - i);
			for (; i + j < n && j < m && s[i + j] == t[j]; j++);
			if (i + j > p + len[p])
				p = i;
		}
	}
	for (int i = 0; i < n; ++i)
		printf("%d\n", len[i]);
}
int main() {
	for (int i = 0; i < 2; ++i) {
		gets(input[i]);
		length[i] = strlen(input[i]);
	}
	prepare(input[0], length[0]);
	solve(input[1], length[1], input[0], length[0]);
}
