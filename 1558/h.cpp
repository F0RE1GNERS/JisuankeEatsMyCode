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
const int N = 20E4 + 10, M = N << 1;
namespace sam {
    char s[M];
    int t[M][26], len[M], fa[M], sz, last, cnt[M];
    void init() {
        memset(t, 0, (sizeof t[0]) * (sz + 10));
        memset(cnt, 0, (sizeof cnt[0]) * (sz + 10));
        last = 1; sz = 2;
    }
    void ins(int ch) {
        int p = last, np = last = sz++; cnt[np] = 1;
        len[np] = len[p] + 1;
        for (; p && !t[p][ch]; p = fa[p]) t[p][ch] = np;
        if (!p) { fa[np] = 1; return; }
        int q = t[p][ch];
        if (len[p] + 1 == len[q]) fa[np] = q;
        else {
            int nq = sz++; len[nq] = len[p] + 1;
            memcpy(t[nq], t[q], sizeof t[0]);
            fa[nq] = fa[q];
            fa[np] = fa[q] = nq;
            for (; t[p][ch] == q; p = fa[p]) t[p][ch] = nq;
        }
    }
    int c[M] = {1}, a[M];
    void rsort() {
        FOR (i, 1, sz) c[i] = 0;
        FOR (i, 1, sz) c[len[i]]++;
        FOR (i, 1, sz) c[i] += c[i - 1];
        FOR (i, 1, sz) a[--c[len[i]]] = i;
        FORD (i, sz - 1, 1) {
            int u = a[i];
            cnt[fa[u]] += cnt[u];
            dbg(u, cnt[u]);
        }
    }
}

using namespace sam;

int main() {
    #ifdef zerol
    freopen("in", "r", stdin);
    #endif // zerol
    int l, r;
    while (~scanf("%s%d%d", s, &l, &r)) {
        init();
         int ll = strlen(s); assert(ll < N);
        FOR (i, 0, strlen(s)) ins(s[i] - 'A');
        rsort();
        LL ans = 0;
        FOR (i, 2, sz) if (cnt[i] >= l && cnt[i] <= r) ans += len[i] - len[fa[i]];
        printf("%lld\n", ans);
    }
}
