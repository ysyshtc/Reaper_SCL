const int MAX_N = 1111111;
int length[2];	//for convience, the index starts from 0
int fail[MAX_N];//longest suffix being the prefix, recursively calculating
char str[2][MAX_N];
void prepare(char *s, int n) {
	fill(fail, fail + n, -1);
	for (int i = 1; i < n; ++i)
		for (int j = i - 1; j >= 0; j = fail[j])
			if (s[fail[j] + 1] == s[i]) {
				fail[i] = fail[j] + 1;
				break;
			}
}
void solve(char *s, int n, char *t, int m) {
	for (int i = 0, j = -1; i < n; ++i) {
		j = s[i] == t[j + 1] ? j + 1 : j > -1 ? i--, fail[j] : -1;
		if (j == m - 1) {
			printf("%d\n", i - m + 1);
			j = fail[j];
		}
	}
}
int main() {
	for (int i = 0; i < 2; ++i) {
		gets(str[i]);
		length[i] = strlen(str[i]);
	}
	prepare(str[0], length[0]);
	solve(str[1], length[1], str[0], length[0]);
}

