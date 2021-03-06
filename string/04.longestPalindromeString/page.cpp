//CF17 - E
typedef long long int64;
const int N = 4 * int(1e6) + 111;
const int mod = 51123987;
int n;
int input[N];
int start[N], finish[N];
int f[N];
int64 ans;
void prepare() {
	int k = 0;
	for (int i = 0; i < n; ++i) {
		if (k + f[k] < i) {
			int &l = f[i] = 0;
			for (; i - l - 1 >= 0 && i + l + 1 < n && input[i - l - 1] == input[i + l + 1]; l++);
			k = i;
		} else {
			int &l = f[i] = f[k - (i - k)];
			if (i + l >= k + f[k]) {
				l = min(l, k + f[k] - i);
				for (; i - l - 1 >= 0 && i + l + 1 < n && input[i - l - 1] == input[i + l + 1]; l++);
				k = i;
			}
		}
		int l = i - f[i], r = i + f[i];
		l += l & 1;
		r -= r & 1;
		if (l <= r) {
			l /= 2;
			r /= 2;
			int mid1 = l + r >> 1;
			int mid2 = mid1 + ((l + r) & 1);
			start[l]++;
			start[mid1 + 1]--;
			finish[mid2]++;
			finish[r + 1]--;
			ans = (ans + (r - l) / 2 + 1) % mod;
		}
	}
}
int main() {
	scanf("%d ", &n);
	for (int i = 0; i < n; ++i) {
		input[i << 1] = getchar();
		if (i < n - 1)
			input[i << 1 | 1] = '*';
	}
	n = n * 2 - 1;
	prepare();
	ans = ans * (ans - 1) / 2 % mod;
	n = (n + 1) / 2;
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		if (i) {
			start[i] = (start[i] + start[i - 1]) % mod;
			finish[i] = (finish[i] + finish[i - 1]) % mod;
		}
		ans = (ans - (int64)start[i] * sum % mod) % mod;
		sum = (sum + finish[i]) % mod;
	}
	cout << (ans + mod) % mod << endl;
}

