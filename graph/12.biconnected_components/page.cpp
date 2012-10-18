const int MAXQ = 11111;
const int MAX_BLOCK = MAXN + MAXN;
struct Edge {
    int next, to, index, access;
    Edge(int n = 0, int t = 0, int id = 0, bool a = false):next(n),to(t),index(id),access(a) {}
} h[MAXM];
struct Query {
    int index, to;
    Query(int i, int t) : index(i), to(t) {}
};
vector<Query> pass[MAX_BLOCK];
int n, m, q, tot, u, v, x[MAXQ], y[MAXQ], ans[MAXQ], lca[MAXQ];
int head[MAXN], belong[MAXM], block_cnt, index_cnt, low[MAXN], dfn[MAXN];
int cut_root[MAX_BLOCK], d_set[MAX_BLOCK];
bool is_cut[MAXN], vis[MAX_BLOCK];
vector<int> ver, edge, chd[MAX_BLOCK];           //stack: edge, ver
inline int find_root(const int &x) { return d_set[x] ? d_set[x] = find_root(d_set[x]) : x; }
inline int d_set_merge(const int &u, const int &v) {
    int p = find_root(u), q = find_root(v);
    return p != q ? d_set[p] = q : q;
}
void dfs(int x) {
    low[x] = dfn[x] = ++index_cnt;
    ver.push_back(x), chd[x].clear();
    for (int i = head[x], k; i; i = h[i].next)
        if (!h[i].access) {
            h[i].access = true, h[i ^ 1].access = true;
            edge.push_back(h[i].index);
            if (dfn[k = h[i].to] == 0) { dfs(k);
                if (low[k] >= dfn[x]) {
                    chd[++block_cnt].clear();
                    is_cut[x] = true;
                    while (edge.back() != h[i].index) {
                        belong[edge.back()] = block_cnt;
                        edge.pop_back();
                    }
                    while (ver.back() != k) {
                        if (is_cut[ver.back()])
                            chd[block_cnt].push_back(ver.back());
                        ver.pop_back();
                    }
                    belong[edge.back()] = block_cnt; //edge:x -> k
                    edge.pop_back();
                    if (is_cut[k]) chd[block_cnt].push_back(k);
                    ver.pop_back();
                    chd[x].push_back(block_cnt);
                }
                low[x] = min(low[x], low[k]);
            }
            else low[x] = min(low[x], dfn[k]);
        }
    //root needs special judge!!!
    //though in this problem, it doesn't matter
}
void build(int x, int c) {
    c += x <= n;
    cut_root[x] = c, vis[x] = true;
    for (int i = 0; i < int(pass[x].size()); ++i)
        if (vis[pass[x][i].to])
            lca[pass[x][i].index] = find_root(pass[x][i].to);
    for (int i = 0; i < int(chd[x].size()); ++i) {
        build(chd[x][i], c);
        d_set_merge(chd[x][i], x);
    }
}
int main(int argc, char* argv[]) {
    while (scanf("%d%d", &n, &m) == 2 && (n || m)) {
        tot = 1;
        for (int i = 1; i <= n; ++i)
            head[i] = 0, dfn[i] = 0, is_cut[i] = false;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &u, &v);
            add_edge(u, v, i + 1), add_edge(v, u, i + 1);
        }
        index_cnt = 0, block_cnt = n;
        for (int i = 1; i <= n; ++i)
            if (dfn[i] == 0) {
                ver.clear(), edge.clear();
                dfs(i);
            }
        for (int i = 1; i <= block_cnt; ++i) {
            pass[i].clear();
            d_set[i] = 0, vis[i] = false;
        }
        scanf("%d", &q);
        for (int i = 0; i < q; ++i) {
            scanf("%d%d", x + i, y + i);
            pass[belong[x[i]]].push_back(Query(i, belong[y[i]]));
            pass[belong[y[i]]].push_back(Query(i, belong[x[i]]));
        }
        for (int i = 1; i <= n; ++i)
            if (is_cut[i] && !vis[i])
                build(i, 0);
        for (int i = 0; i < q; ++i) {
            ans[i] = cut_root[belong[x[i]]] + cut_root[belong[y[i]]] - 2 * cut_root[lca[i]];
            if (lca[i] <= n) ++ans[i];
        }
        for (int i = 0; i < q; ++i) printf("%d\n", ans[i]);
    }
}

