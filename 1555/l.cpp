#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "DEBUG: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
#ifdef ONLINE_JUDGE
#define assert(condition) if (!(condition)) { int x = 1, y = 0; cout << x / y << endl; }
#endif
void err() { cout << "" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

struct Edge {
    Edge(int t, int c) : to(t), cost(c) { }
    int to, cost;
};

struct HeapNode {
    HeapNode(LL _d, int _u, int _k)
        : d(_d), u(_u), k(_k) { }
    LL d; int u, k;
    bool operator < (const HeapNode &x) const {
        return d > x.d || (d == x.d && (u < x.u || (u == x.u && k < x.k)));
    }
};

const LL INF = 1E18;
const int N = 1E5 + 100, K = 12;
int n, m, done[N][K];
LL dis[N][K];
vector<Edge> g[N];

int main() {
    int T; cin >> T;
    while (T--) {
        memset(done, 0, sizeof done);
        fill(dis[0], dis[0] + N * K, INF);
        dis[1][0] = 0;
        int limit;
        scanf("%d%d%d", &n, &m, &limit);
        FOR (i, 1, n + 1) g[i].clear();
        FOR (i, 0, m) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            g[u].emplace_back(v, w);
        }
        priority_queue<HeapNode> q;
        q.emplace(0, 1, 0); dis[1][0] = 0;
        while (!q.empty()) {
            HeapNode x = q.top(); q.pop();
            int u = x.u, k = x.k;
            if (done[u][k]) continue;
            done[u][k] = 1;
            dbg(u, k, dis[u][k]);
            for (Edge &e: g[u]) {
                if (k < limit && !done[e.to][k + 1] && dis[e.to][k + 1] > dis[u][k]) {
                    dis[e.to][k + 1] = dis[u][k];
                    q.emplace(dis[e.to][k + 1], e.to, k + 1);
                }
                if (!done[e.to][k] && dis[e.to][k] > dis[u][k] + e.cost) {
                    dis[e.to][k] = dis[u][k] + e.cost;
                    q.emplace(dis[e.to][k], e.to, k);
                }
            }
        }
        LL ans = dis[n][0];
        FOR (i, 1, limit + 1) ans = min(ans, dis[n][i]);
        cout << ans << endl;
    }
}
