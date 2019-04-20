#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
#else
#define dbg(...)
#endif // zerol
void err() { cout << "\033[39;0m" << endl; }
template<typename T, typename... A>
void err(T a, A... x) { cout << a << ' '; err(x...); }
// ----------------------------------------------------------------------------------------

typedef pair<int, int> P;

const int N = 1e5+10;

int a[N], sz[N], son[N], fa[N], idx[N], dep[N], link[N], cnt;

int add(int p) {
    while(p<N) {
        ++a[p];
        p += p&-p;
    }
}

int sum(int p) {
    int ret = 0;
    while(p) {
        ret += a[p];
        p &= p-1;
    }
    return ret;
}

struct Edge {
    int u, v, w;
};

struct Query {
    int u, v, w;
    int *des;
};

template<typename T>
bool cmp(const T& p, const T&  q) {
    return p.w<q.w;
}

vector<int> G[N];

int ant[N];

Edge edges[N];
Query queries[N];

void dfs1(int p, int _fa) {
    fa[p] = _fa; ++sz[p];
    for(auto q: G[p]) if(q != _fa) {
        dep[q] = dep[p]+1;
        dfs1(q, p);
        sz[p] += sz[q];
        if(!son[p] || sz[q]>sz[son[p]]) son[p] = q;
    }
}

void dfs2(int p) {
    idx[p] = ++cnt;
    if(p != son[fa[p]]) link[p] = p; else link[p] = link[fa[p]];
    if(son[p]) {
        dfs2(son[p]);
    }
    for(auto q: G[p]) if(q != fa[p] && q != son[p]) {
        dfs2(q);
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    FOR(i, 1, n) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        edges[i] = {u, v, w};
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    sort(edges+1, edges+n, cmp<Edge>);
    dfs1(1, 0);
    dfs2(1);
    FOR(i, 0, m) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        queries[i] = {u, v, w, ant+i};
    }
    sort(queries, queries+m, cmp<Query>);
    int p = 1;
    FOR(i, 0, m) {
        while(p<n && edges[p].w<=queries[i].w) {
            int u = edges[p].u, v = edges[p].v;
            if(u == fa[v]) add(idx[v]); else add(idx[u]);
            ++p;
        }
        int u = queries[i].u, v = queries[i].v;
        int ans = 0;
        while(u != v) {
            if(dep[link[u]]<dep[link[v]]) swap(u, v);
            if(link[u] == link[v]) {
                if(dep[u]<dep[v]) swap(u, v);
                ans += sum(idx[u]) - sum(idx[v]);
                break;
            }
            ans += sum(idx[u]) - sum(idx[link[u]]-1);
            u = fa[link[u]];
        }
        *queries[i].des = ans;
    }
    FOR(i, 0, m) printf("%d\n", ant[i]);
    return 0;
}