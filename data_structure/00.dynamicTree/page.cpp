#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>
#include <numeric>
#include <climits>
#include <string>
#include <iomanip>
#include <cctype>
#include <bitset>
#include <cmath>
#include <vector>
#include <ctime>
#include <queue>
#include <map>
#include <set>
using namespace std;

const int MAX_N = 111111;
const int INF = (int)1e9;

struct Node {
	int fa, tp, cost, maxc, flag, lc, rc;
	bool rev;
	void clear() {
		tp = 2;
		fa = lc = rc = rev = 0;
	}
	Node(int f = 0, int c = 0) {
		clear();
		fa = f;
		cost = maxc = c;
	}
	int&operator [](int p) {
		return p ? rc : lc;
	}
};

struct DynamicTree {
	int stk[MAX_N], top;
	Node tree[MAX_N];
	void clear(int n) {
		top = 0;
		for (int i = 1; i <= n; ++i)
			tree[i].clear();
	}
	void reverse(int p) {
		tree[tree[p].lc].tp = 1;
		tree[tree[p].rc].tp = 0;
		swap(tree[p].lc, tree[p].rc);
		tree[tree[p].lc].rev = !tree[tree[p].lc].rev;
		tree[tree[p].rc].rev = !tree[tree[p].rc].rev;
	}
	void update(int p) {
		tree[p].maxc = max(max(tree[tree[p].lc].maxc, tree[tree[p].rc].maxc), tree[p].cost);
	}
	void adjust(int p, int c) {
		tree[p].flag += c;
		tree[p].maxc += c;
		tree[p].cost += c;
	}
	void release(int p) {
		if (tree[p].rev) {
			reverse(p);
			tree[p].rev = false;
		}
		if (tree[p].flag) {
			adjust(tree[p].lc, tree[p].flag);
			adjust(tree[p].rc, tree[p].flag);
			tree[0].maxc = -INF;			//important!!!!
			tree[p].flag = 0;
		}
	}
	void fix(int p, int fa, int t) {
		tree[p].tp = t;
		tree[p].fa = fa;
		if (t != 2)
			tree[fa][t] = p;
	}
	void rotate(int p) {
		int fa = tree[p].fa, tmp = tree[p].tp;
		fix(p, tree[fa].fa, tree[fa].tp);
		fix(tree[p][1 - tmp], fa, tmp);
		fix(fa, p, 1 - tmp);
		update(fa);
	}
	void splay(int p) {
		int it = p;
		top = 0;
		for (; tree[it].tp != 2; it = tree[it].fa)
			stk[++top] = it;
		stk[++top] = it;
		for (; top; release(stk[top--]));
		while (tree[p].tp != 2) {
			it = tree[p].fa;
			if (tree[it].tp == 2)
				rotate(p);
			else if (tree[p].tp != tree[it].tp)
				rotate(p), rotate(p);
			else
				rotate(it), rotate(p);
		}
		update(p);
	}
	void link(int u, int v) {
		tree[tree[u].rc].tp = 2;
		tree[u].rc = v;
		tree[v].tp = 1;
	}
	void access(int u) {
		for (int v = 0; u; v = u, u = tree[u].fa) {
			splay(u);
			link(u, v);
			update(u);
		}
	}
	int findRoot(int u) {
		access(u);
		splay(u);
		int v = u;
		for (; tree[v].lc; v = tree[v].lc);
		splay(v);
		return v;
	}
	void setRoot(int p) {
		access(p);
		splay(p);
		reverse(p);
		//update(p);
	}
	void join(int u, int v) {
		setRoot(u);
		tree[u].fa = v;
		access(u);
	}
	void cut(int u, int v) {
		setRoot(u);
		access(v);
		splay(v);
		tree[tree[v].lc].fa = 0;
		tree[tree[v].rc].tp = 2;
		tree[v].lc = 0;
		update(v);
	}
	int lca(int u, int v) {
		int ret = 0;
		access(u);
		for (int chd = 0; v; chd = v, v = tree[v].fa) {
			splay(v);
			if (tree[v].fa == 0)
				ret = v;
			link(v, chd);
			update(v);
		}
		return ret;
	}
	void modify(int u, int v, int c) {
		access(u);
		for (int chd = 0; v; chd = v, v = tree[v].fa) {
			splay(v);
			if (tree[v].fa == 0) {
				adjust(tree[v].rc, c);
				adjust(chd, c);
				tree[0].maxc = -INF;
				tree[v].cost += c;
			}
			link(v, chd);
			update(v);
		}
	}
	int query(int u, int v) {
		int ret = -INF;
		access(u);
		for (int chd = 0; v; chd = v, v = tree[v].fa) {
			splay(v);
			if (tree[v].fa == 0)
				ret = max(max(tree[tree[v].rc].maxc, tree[chd].maxc), tree[v].cost);
			link(v, chd);
			update(v);
		}
		return ret;
	}
};

int main() {
}

