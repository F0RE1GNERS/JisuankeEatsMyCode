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
const int maxn = 2E6 + 100;
LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }


namespace pam {
    int t[maxn][10], fa[maxn], len[maxn], rs[maxn], num[maxn], cnt[maxn], mp[maxn];
    int sz, n, last;
    vector<int> G[maxn];
    int N(int l) {
        memset(t[sz], 0, sizeof t[0]);
        len[sz] = l;
        return sz++;
    }
    void init() {
        rs[n = sz = 0] = -1;
        last = N(0);
        fa[last] = N(-1);
    }
    int get_fa(int x) {
        while (rs[n - 1 - len[x]] != rs[n]) x = fa[x];
        return x;
    }
    void ins(int ch) {
        rs[++n] = ch;
        int p = get_fa(last);
        if (!t[p][ch]) {
            int np = N(len[p] + 2);
            fa[np] = t[get_fa(fa[p])][ch];
            num[np] = num[fa[np]] + 1;
            t[p][ch] = np;
            cnt[np] = 1;
        }
        last = t[p][ch];
        mp[last] = ch;
    }
//    void get_cnt() { FORD (i, sz - 1, 0) cnt[fa[i]] += cnt[i]; }
}

char s[maxn];
using namespace pam;
LL ans;
const LL MOD = 1E9 + 7, INV10 = get_inv(10, MOD);
LL l[maxn], r[maxn], pp[maxn] = {1};

void dfs(int u, int fa) {
    FOR (i, 0, 10) if (t[u][i]) dfs(t[u][i], u);
    if (u == 0 || u == 1) return;
    r[u] += 1; l[u] += pp[len[u] - 1];
    if (len[u] == 1) r[u] = 0;
    l[u] %= MOD; r[u] %= MOD;
//    dbg(u, len[u], mp[u], l[u], r[u]);
    ans = (ans + mp[u] * (l[u] + r[u])) % MOD;
    l[fa] += l[u] * INV10 % MOD;
    r[fa] += r[u] * 10 % MOD;
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    FOR (i, 1, maxn) pp[i] = pp[i - 1] * 10 % MOD;
    pam::init();
    scanf("%s", s);
    FOR (i, 0, strlen(s)) ins(s[i] - '0');
//    FOR (i, 2, sz) {
//        dbg(i, fa[i]);
//        G[fa[i]].push_back(i);
//    }
    dfs(0, -1);
    dbg(ans);
    dfs(1, -1);
    cout << ans << endl;
}
