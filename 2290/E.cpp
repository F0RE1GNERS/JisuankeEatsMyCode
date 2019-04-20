#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cout << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cout << a << ' '; err(x...); }
#else
#define dbg(...)
#endif
// -----------------------------------------------------------------------------
const int N = 2E5 + 100;
int a[N];
struct P { int v, r; };
bool operator < (const P& a, const P& b) {
    return a.v < b.v;
}
set<P> S[2];
int sa[N];

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    int T; cin >> T;
    FOR (Ca, 1, T + 1) {
        S[0].clear(); S[1].clear();
        printf("Case %d:\n", Ca);
        int n, m; cin >> n >> m;
        FOR (i, 0, n) scanf("%d", a + i);
        a[n] = m;
        int ml = 1E9, mr = -1;
        auto upd = [&](int l, int r) {
            int d = r - l;
            if (d < 0) return;
            if (d > mr - ml || (d == mr - ml && l < ml)) {
                ml = l; mr = r;
            }
        };
        FOR (i, 0, n) upd(a[i] + 1, a[i + 1] - 1);
        upd(0, a[0] - 1);
        sa[n - 1] = a[n - 1];
        FORD (i, n - 2, -1) sa[i] = a[i] ^ sa[i + 1];

        S[n & 1].insert({0, m - 1});
        FORD (i, n - 2, -1) {
//            P p = {sa[i + 1], a[i + 2] - 1};
            P p = {sa[i + 1], a[i + 1] - 1};
            auto &cur = S[i & 1], &nxt = S[(i + 1) & 1];
            auto it = nxt.lower_bound(p);
            if (it == nxt.end() || it->v != p.v)
                nxt.insert(p);
            auto zz = cur.lower_bound({sa[i], -1});
            dbg(i, a[i], sa[i], zz->v, zz->r);
            if (zz->v == sa[i]) {
                upd(i ? a[i - 1] + 1 : 0, zz->r);
            }
        }
        if (mr == -1) puts("0");
        else cout << mr - ml + 1 << endl << ml << ' ' << mr << endl;
    }
}