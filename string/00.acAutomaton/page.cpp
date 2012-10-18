//POJ3897 - Computer Virus on Planet Pandora
typedef unsigned long long Bit;
const int N = 250010, M = 5100100;
struct Node {
	int x;
	Node *ch[26], *pre;
	Bit state[4];
};
int n, top, m;
char input[M], str[M];
Node data[N], *root;
Node *newNode(char x) {
	Node *p = data + top++;
	p->x = x;
	for (int i = 0; i < 26; ++i)
		p->ch[i] = 0;
	p->pre = 0;
	p->state[0] = p->state[1] = p->state[2] = p->state[3] = 0ULL;
	return p;
}
void modify(Node *p, int x) {
	p->state[x >> 6] |= 1ULL << (x & 63);
}
void update(Bit *a, Bit *b) {
	a[0] |= b[0];
	a[1] |= b[1];
	a[2] |= b[2];
	a[3] |= b[3];
}
void build() {
	static Node *que[N], *father[N];
	int r = 1;
	que[0] = father[0] = root;
	for (int i = 0; i < r; ++i) {
		Node *t = que[i];
		Node *f = father[i];
		//get false pointer
		t->pre = root;
		if (t != root && f != root) {
			for (Node *p = t; ;) {
				p = p == t ? f : p->pre;
				if (p->pre->ch[t->x] && p->pre->ch[t->x] != t) {
					t->pre = p->pre->ch[t->x];
					update(t->state, t->pre->state);
					break;
				}
				if (p == root)
					break;
			}
		}
		//add its son to the queue
		for (int i = 0; i < 26; ++i)
			if (t->ch[i]) {
				que[r] = t->ch[i];
				father[r] = t;
				r++;
			}
	}
}
Bit res[4];
void solve(int start, int end, int delta) {
	Node *now = root;
	for (int i = start; i != end; i += delta) {
		int k = str[i] - 'A';
		if (now->ch[k]) {
			now = now->ch[k];
		} else {
			for (;;) {
				now = now->pre;
				if (now->ch[k]) {
					now = now->ch[k];
					break;
				}
				if (now == root)
					break;
			}
		}
		update(res, now->state);
	}
}
int main() {
	int tests;
	scanf("%d", &tests);
	while (tests--) {
		//build trie
		top = 0;
		root = newNode(0);
		scanf("%d\n", &n);
		for (int i = 0; i < n; ++i) {
			gets(input);
			m = strlen(input);
			Node *now = root;
			for (int j = 0; j < m; ++j) {
				int c = input[j] - 'A';
				if (!now->ch[c]) {
					now->ch[c] = newNode(c);
				}
				now = now->ch[c];
			}
			modify(now, i);
		}
		//build automaton
		build();
		gets(input);
		n = strlen(input);
		m = 0;
		for (int i = 0; i < n; )
			if (isalpha(input[i])) {
				str[m++] = input[i++];
			} else {
				i++;
				int x = 0;
				for (; isdigit(input[i]); i++)
					x = x * 10 + input[i] - '0';
				for (int j = 1; j <= x; ++j)
					str[m++] = input[i];
				i += 2;
			}
		memset(res, 0, sizeof(res));
		solve(0, m, 1);
		solve(m - 1, -1, -1);
		int cnt = 0;
		for (int i = 0; i < 64; ++i)
			for (int j = 0; j < 4; ++j)
				if (res[j] >> i & 1ULL)
					cnt++;
		printf("%d\n", cnt);
	}
}
