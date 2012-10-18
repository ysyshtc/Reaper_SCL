//HDU4286 - Data Handler
#pragma comment(linker, "/STACK:16777216")
const int N = 1111111;
struct Node {
	Node *pre, *ch[2];
	int key, rev, size;
};
Node dataPool[N], *null, *root;
int poolTop;
Node *newNode(int x) {
	Node *p = dataPool + poolTop++;
	p->key = x;
	p->rev = 0;
	p->size = 1;
	p->ch[0] = p->ch[1] = p->pre = null;
	return p;
}
void makeSame(Node *x) {
	x->rev ^= 1;
	swap(x->ch[0], x->ch[1]);
}
void pushDown(Node *x) {
	if (x->rev) {
		x->rev = 0;
		makeSame(x->ch[0]);
		makeSame(x->ch[1]);
	}
}
void update(Node *x) {
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
}
void rotate(Node *x, int c) {
	Node *y = x->pre;
	pushDown(y), pushDown(x);
	y->ch[!c] = x->ch[c], x->pre = y->pre;
	if (x->ch[c] != null)
		x->ch[c]->pre = y;
	if (y->pre != null)
		y->pre->ch[y == y->pre->ch[1]] = x;
	y->pre = x, x->ch[c] = y, update(y);
	if (y == root)
		root = x;
}
void splay(Node *x, Node *f) {
	for (pushDown(x); x->pre != f; )
		if (x->pre->pre == f)
			rotate(x, x == x->pre->ch[0]);
		else {
			Node *y = x->pre, *z = y->pre;
			if (z->ch[0] == y)
				if (y->ch[0] == x)
					rotate(y, 1), rotate(x, 1);
				else
					rotate(x, 0), rotate(x, 1);
			else
				if (y->ch[1] == x)
					rotate(y, 0), rotate(x, 0);
				else
					rotate(x, 1), rotate(x, 0);
		}
	update(x);
}
void select(int k, Node *f) {
	Node *now = root;
	for (;;) {
		pushDown(now);
		int tmp = now->ch[0]->size;
		if (tmp + 1 == k)
			break;
		if (k <= tmp)
			now = now->ch[0];
		else
			k -= tmp + 1, now = now->ch[1];
	}
	splay(now, f);
}
void getInterval(int l, int r) {	//[l, r]
	select(l, null);
	select(r + 2, root);
}
void insert(int k, int x) { //0 <= k <= length
	select(k + 1, null);
	select(k + 2, root);
	root->ch[1]->ch[0] = newNode(x);
	root->ch[1]->ch[0]->pre = root->ch[1];
	update(root->ch[1]);
	update(root);
}
void deletx(int k) {
	getInterval(k, k);
	root->ch[1]->ch[0] = null;
	update(root->ch[1]);
	update(root);
}
int n, m, lft, rgt;
void initialize() {
	poolTop = 0;
	null = newNode(0);
	null->size = 0;
	null->ch[0] = null->ch[1] = null->pre = null;
	root = newNode(0);
	root->ch[1] = newNode(0);
	root->ch[1]->pre = root;
	update(root);
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		insert(i, x);
	}
}
vector<int> v;
void print(Node *x) {
	pushDown(x);
	if (x->ch[0] != null)
		print(x->ch[0]);
	v.push_back(x->key);
	if (x->ch[1] != null)
		print(x->ch[1]);
}
void output() {
	v.clear();
	print(root);
	int t = (int)v.size() - 1;
	for (int i = 1; i < t; ++i)
		printf("%d%c", v[i], i < t - 1 ? ' ' : '\n');
}
void solve() {
	static char buf[111];
	int x;
	scanf("%d%d%d", &lft, &rgt, &m);
	lft--;
	while (m--) {
		scanf("%s", buf);
		if (buf[0] == 'M') {
			if (buf[4] == 'L') {
				scanf("%s", buf);
				if (buf[0] == 'L')
					lft = max(lft - 1, 0);
				else
					rgt = max(rgt - 1, 0);
			} else {
				scanf("%s", buf);
				if (buf[0] == 'L')
					lft = min(lft + 1, n);
				else
					rgt = min(rgt + 1, n);
			}
		} else if (buf[0] == 'I') {
			scanf("%s%d", buf, &x);
			if (buf[0] == 'L')
				insert(lft, x);
			else
				insert(rgt, x);
			rgt++;
		} else if (buf[0] == 'D') {
			scanf("%s%d", buf, &x);
			if (buf[0] == 'L')
				deletx(lft + 1);
			else
				deletx(rgt);
			rgt--;
		} else if (buf[0] == 'R') {
			getInterval(lft + 1, rgt);
			makeSame(root->ch[1]->ch[0]);
		}
	}
	
	output();
}
int main() {
	int tests;
	cin >> tests;
	while (tests--) {
		initialize();
		solve();
	}
}
