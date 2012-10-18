int n, m, minE[N], s[M], t[M], c[N], v[N];
double cost[M], w[N];
double directed_MST(int root) {
    for (double tmp = 0; ; ) {
        for (int i = 1; i <= n; i++) minE[i] = -1;
        for (int i = 1; i <= m; i++) if (s[i] != t[i])
            if (minE[t[i]] == -1 || cost[i] < cost[minE[t[i]]]) minE[t[i]] = i;
        for (int i = 1; i <= n; i++) 
            if (i != root && minE[i] == -1) return -1e9;
        int cnt = 0;
        for (int i = 1; i <= n; i++) c[i] = v[i] = 0;
        for (int i = 1; i <= n; i++) 
        if (i != root) {
            tmp += cost[minE[i]];
            if (!v[i]) {
                int j = i;
                for (; j != root && v[j] != i && !c[j]; j = s[minE[j]]) v[j] = i;
                if (j != root && !c[j]) {
                    c[j] = ++cnt;
                    for (int k = s[minE[j]]; k != j; k = s[minE[k]]) c[k] = cnt;
                }
            }
        }
        if (!cnt) return tmp;
        for (int i = 1; i <= n; i++) 
            if (!c[i]) c[i] = ++cnt;
        w[root] = 0;
        for (int i = 1; i <= n; i++) if (i != root) w[i] = cost[minE[i]];
        for (int i = 1; i <= m; i++) {
            if (c[s[i]] != c[t[i]]) cost[i] -= w[t[i]];
            s[i] = c[s[i]]; t[i] = c[t[i]];
        }
        n = cnt; root = c[root];
    }
}

