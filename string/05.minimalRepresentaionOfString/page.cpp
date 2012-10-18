//ZOJ1729 - Hidden Password
const int N = 222222;
int n;
char input[N];
int main() {
	int tests;
	scanf("%d", &tests);
	while (tests--) {
		scanf("%d ", &n);
		gets(input);
		for (int i = 0; i < n; ++i)
			input[i + n] = input[i];
		int pos = 0;
		for (int i = 1, k; i < n; ) {
			for (k = 0; k < n && input[pos + k] == input[i + k]; k++);
			if (k < n && input[i + k] < input[pos + k]) {
				int t = pos;
				pos = i;
				i = max(i + 1, t + k + 1);
			} else {
				i += k + 1;
			}
		}
		printf("%d\n", pos);
	}
}

