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
// ----------------------------------------------------------------------------
const int N = 1E5 + 100;
LL n, v[N];

namespace bit {
    LL cc[N], c[N];
    inline LL lowbit(LL x) { return x & -x; }
    void add(LL x, LL v) {
        for (LL i = x; i <= N; i += lowbit(i)) {
            cc[i] += (n + 1 - x) * v;
            c[i] += v;
        }
    }
    void add(LL l, LL r, LL v) { add(l, v); add(r + 1, -v); }
    LL sum(LL x, LL d) {
        LL ret = 0;
        for (LL i = x; i > 0; i -= lowbit(i))
            ret += cc[i] + c[i] * d;
        return ret;
    }
    LL query(LL l, LL r) {
        LL d = (r - l + 1) - (n + 1 - l);
        return sum(r, d) - sum(l - 1, d);
    }
}

int main() {
    int Q; cin >> n >> Q;
    FOR (i, 1, n + 1) {
        LL t; scanf("%lld", &t);
        bit::add(i, t);
        v[i] = t;
    }
    while (Q--) {
        LL tp, a, b; scanf("%lld%lld%lld", &tp, &a, &b);
        if (tp == 2) {
            bit::add(a, b - v[a]);
            v[a] = b;
        } else {
            LL ans = bit::query(a, b);
            printf("%lld\n", ans);
        }
    }
}
