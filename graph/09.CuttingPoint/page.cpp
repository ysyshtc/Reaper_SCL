int trajan(int i, int fa) {
	dfn[i] = low[i] = ++ord;
	int res = 0, tmp = 0, son = 0;
	for (int j = f[i]; j; j = t[j])
	if (p[j] != fa) {
		if (!dfn[p[j]]) {
			son++;
			res = max(res, trajan(p[j], i));
			low[i] = min(low[i], low[p[j]]);
			if (dfn[i] <= low[p[j]]) tmp++;
		}
		low[i] = min(low[i], dfn[p[j]]);
	}
	if (fa == -1) tmp = son;
	else if (tmp) tmp++;
	res = max(res, tmp);
	return res;
}

