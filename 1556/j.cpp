#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[32;1m" << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
const int N = 1E5 + 100, B = 250;

namespace bit {
    LL c[N];
    inline int lowbit(int x) { return x & -x; }
    void add(int x, LL v) {
        for (; x < N; x += lowbit(x))
            c[x] += v;
    }
    LL sum(int x) {
        LL ret = 0;
        for (; x > 0; x -= lowbit(x))
            ret += c[x];
        return ret;
    }
}

vector<int> dep[N], G[N], mdep;
vector<LL> psum[N];
int in[N], out[N], clk;
LL S[N];
void dfs(int u, int d = 0) {
    in[u] = ++clk;
    dep[d].push_back(u);
    for (int& v: G[u])
        dfs(v, d + 1);
    out[u] = clk;
}

int main() {
    int n, Q; cin >> n >> Q;
    FOR (_, 1, n) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
    dfs(1);
    FOR (i, 0, n + 1)
        if (dep[i].size() >= B) {
            dbg(i);
            mdep.push_back(i);
            psum[i].resize(N);
            for (int& u: dep[i])
                psum[i][in[u]]++;
            FOR (j, 1, n + 1) psum[i][j] += psum[i][j - 1];
        }
    while (Q--) {
        int tp; scanf("%d", &tp);
        if (tp == 1) {
            int d, x; scanf("%d%d", &d, &x);
            if (dep[d].size() < B)
                for (int& u: dep[d]) bit::add(in[u], x);
            S[d] += x;
        } else {
            int u; scanf("%d", &u);
            LL ans = bit::sum(out[u]) - bit::sum(in[u] - 1);
            dbg(ans);
            for (int& d: mdep) ans += (psum[d][out[u]] - psum[d][in[u] - 1]) * S[d];
            printf("%lld\n", ans);
        }
    }
}
