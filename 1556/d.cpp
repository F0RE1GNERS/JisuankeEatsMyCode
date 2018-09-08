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

const int N = 2E3 + 100;
const LL INF = 1E9;
LL n, m, s, t, k;
LL done[N], dist[N];

struct HeapNode {
    LL v, c;
    bool operator < (const HeapNode &x) const {
        return c + dist[v] > x.c + dist[x.v];
    }
};

struct Edge {
    LL to, cost;
};

vector<Edge> G[N], rG[N];

void dijkstra(LL s) {
    memset(done, 0, sizeof done);
    FOR (i, 1, n + 1) dist[i] = INF;
    dist[s] = 0;
    priority_queue<HeapNode> q;
    q.push({s, 0});
    while (!q.empty()) {
        HeapNode x = q.top(); q.pop();
        LL u = x.v;
        if (done[u]) continue;
        done[u] = 1;
        for (Edge &e: G[u]) {
            LL v = e.to;
            if (!done[v] && dist[v] > dist[u] + e.cost) {
                dist[v] = dist[u] + e.cost;
                q.push({v, dist[v]});
            }
        }
    }
}

LL astar() {
    priority_queue<HeapNode> q;
    q.push({s, 0}); k--;
    while (!q.empty()) {
        HeapNode pre = q.top(); q.pop();
        LL u = pre.v;
        if (u == t) {
            if (k) k--;
            else return pre.c;
        }
        for (Edge &e: rG[u]) {
            LL v = e.to;
            q.push({v, pre.c + e.cost});
        }
    }
    return INF;
}

void addedge(LL u, LL v, LL w) {
    G[v].push_back({u, w});
    rG[u].push_back({v, w});
}

int main() {
    while (cin >> n >> m) {
        LL limit;
        cin >> s >> t >> k >> limit;
        FOR (i, 1, n + 1) { G[i].clear(); rG[i].clear(); }
        FOR (i, 0, m) {
            LL u, v, w; scanf("%lld%lld%lld", &u, &v, &w);
            addedge(u, v, w);
        }
        dijkstra(t);
        // cout << dist[s] << endl;
        // int p = astar(); dbg(p);
        if (dist[s] == INF || astar() > limit) {
            puts("Whitesnake!");
        } else {
            puts("yareyaredawa");
        }
    }
}
