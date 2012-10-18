const int N = 111111;
int n;
int lc[N], rc[N], key[N], aux[N], size[N], top, root;
//int maxValue[N];	mark info
void lRotate(int &x) {
	int y = rc[x];
	rc[x] = lc[y];
	lc[y] = x;
	size[y] = size[x];
	size[x] = size[lc[x]] + size[rc[x]] + 1;
	//update mark info
	x = y;
}
void rRotate(int &x) {
	int y = lc[x];
	lc[x] = rc[y];
	rc[y] = x;
	size[y] = size[x];
	size[x] = size[lc[x]] + size[rc[x]] + 1;
	//update mark info
	x = y;
}
void insert(int &k, int x) {
	if (!k) {
		k = ++top;
		key[k] = x;
		aux[k] = rand();
		size[k] = 1;
		return;
	}
	++size[k];
	//update mark info
	if (x <= key[k]) {
		insert(lc[k], x);
		if (aux[lc[k]] < aux[k])
			rRotate(k);
	} else {
		insert(rc[k], x);
		if (aux[rc[k]] < aux[k])
			lRotate(k);
	}
}
int erase(int &k, int x) {
	--size[k];
	if (key[k] == x || x > key[k] && rc[k] == 0) {
		if (!lc[k] || !rc[k]) {
			int ret = key[k];
			k = lc[k] + rc[k];
			return ret;
		}
		return key[k] = erase(lc[k], x + 1);
	}
	return erase(x < key[k] ? lc[k] : rc[k], x);
}
int findkth(int k) {	//1 <= k <= treapSize
	int now = root;
	while (now) {
		//if have, push down mark info
		int tmp = size[lc[now]];
		if (k == tmp + 1)
			return key[now];
		if (k <= tmp)
			now = lc[now];
		else
			now = rc[now], k -= tmp + 1;
	}
	return -1;
}
void initialize() {
	memset(lc, 0, sizeof(lc));
	memset(rc, 0, sizeof(rc));
	root = top = 0;
}
