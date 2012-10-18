int n, m, tot, head[MAXN], f[MAXN], bridge[MAXN], dfn[MAXN], low[MAXN], u, v, bridge_cnt;
int task, q, dep[MAXN], cnt;
bool vis[MAXN];
inline int find_root(const int&x){return f[x]?f[x]=find_root(f[x]):x;}
inline int merge(const int &u, const int &v) {
    int p = find_root(u), q = find_root(v);
    return p != q ? f[p] = q : q;
}
int dfs(int x, int path) {
    dfn[x] = low[x] = ++cnt;
    for (int i = head[x], k; i; i = h[i].next)
        if (dfn[k = h[i].to] == 0)
            low[x] = min(low[x], dfs(k, i));
        else if (i != (path ^ 1))
            low[x] = min(low[x], dfn[k]);
    return low[x];
}
void build(int x, int last) {
    if (low[x] == dfn[x]) {
        ++bridge_cnt, bridge[x] = last;
        dep[x] = dep[last] + 1;
        last = x;
    }
    else f[x] = last;
    vis[x] = true;
    for (int i = head[x], k; i; i = h[i].next)
        if (!vis[k = h[i].to]) build(k, last);
}
int main(int argc, char* argv[]) {
    while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
        tot = 1;
        for (int i = 1; i <= n; ++i) {
            head[i] = 0, f[i] = 0, dfn[i] = 0;
            dep[i] = 0, bridge[i] = 0, vis[i] = false;
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v), add_edge(v, u);
        }
        cnt = 0, bridge_cnt = -1;
        dfs(1, -1);
        build(1, 0);
        printf("Case %d:\n", ++task);
        for (scanf("%d", &q); q--; ) {
            scanf("%d%d", &u, &v);
            for (int p1=find_root(u), p2=find_root(v); p1 != p2; ) {
                if (dep[p1] < dep[p2])
                    p2 = merge(p2, bridge[p2]);
                else
                    p1 = merge(p1, bridge[p1]);
                --bridge_cnt;
            }
            printf("%d\n", bridge_cnt);
        }
        printf("\n");
    }
}

