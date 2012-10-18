//HDU2966 - In case of failure
typedef long long int64;
struct Point {
	int x, y;
};
inline int64 sqr(int x) {
	return (int64)x * x;
}
inline int64 dist(const Point &a, const Point &b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}
struct Rectangle {
	int lx, rx, ly, ry;
	void set(const Point &p) {
		lx = rx = p.x;
		ly = ry = p.y;
	}
	void merge(const Rectangle &o) {
		lx = min(lx, o.lx);
		rx = max(rx, o.rx);
		ly = min(ly, o.ly);
		ry = max(ry, o.ry);
	}
	int64 dist(const Point &p) {
		if (p.x <= lx && p.y <= ly)
			return sqr(p.x - lx) + sqr(p.y - ly);
		if (p.x <= rx && p.y <= ly)
			return sqr(p.y - ly);
		if (p.x >= rx && p.y <= ly)
			return sqr(p.x - rx) + sqr(p.y - ly);
		if (p.x >= rx && p.y <= ry)
			return sqr(p.x - rx);
		if (p.x >= rx && p.y >= ry)
			return sqr(p.x - rx) + sqr(p.y - ry);
		if (p.x >= lx && p.y >= ry)
			return sqr(p.y - ry);
		if (p.x <= lx && p.y >= ry)
			return sqr(p.x - lx) + sqr(p.y - ry);
		if (p.x <= lx && p.y >= ly)
			return sqr(p.x - lx);
		return 0;
	}
};
struct Node {
	Point p;
	Rectangle rect;
};
const int MAX_N = 111111;
const int64 INF = 1LL << 60;
int n;
Point a[MAX_N], b[MAX_N];
Node tree[MAX_N * 3];
Point p;
int64 result;
bool cmpX(const Point &a, const Point &b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}
bool cmpY(const Point &a, const Point &b) {
	return a.y < b.y || a.y == b.y && a.x < b.x;
}
void build(int k, int s, int t, bool d) {
	int mid = s + t >> 1;
	nth_element(a + s, a + mid, a + t, d ? cmpX : cmpY);
	tree[k].p = a[mid];
	tree[k].rect.set(a[mid]);
	if (s < mid) {
		build(k << 1, s, mid, d ^ 1);
		tree[k].rect.merge(tree[k << 1].rect);
	}
	if (mid + 1 < t) {
		build(k << 1 | 1, mid + 1, t, d ^ 1);
		tree[k].rect.merge(tree[k << 1 | 1].rect);
	}
}
void query(int k, int s, int t, bool d) {
	if (tree[k].rect.dist(p) >= result)
		return;
	int64 temp = dist(tree[k].p, p);
	if (temp && temp < result)
		result = temp;
	int mid = s + t >> 1;
	if (d && cmpX(p, tree[k].p) || !d && cmpY(p, tree[k].p)) {
		if (s < mid)
			query(k << 1, s, mid, d ^ 1);
		if (mid + 1 < t)
			query(k << 1 | 1, mid + 1, t, d ^ 1);
	} else {
		if (mid + 1 < t)
			query(k << 1 | 1, mid + 1, t, d ^ 1);
		if (s < mid)
			query(k << 1, s, mid, d ^ 1);
	}
}
int main() {
	int tests;
	for (scanf("%d", &tests); tests--; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &a[i].x, &a[i].y);
			b[i] = a[i];
		}
		build(1, 0, n, 0);
		for (int i = 0; i < n; ++i) {
			p = b[i];
			result = INF;
			query(1, 0, n, 0);
			printf("%lld\n", result);
		}
	}
}
