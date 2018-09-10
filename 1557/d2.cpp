#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[31;1m" << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
const int N = 2E6 + 100;

namespace dujiao {
    const int M = 5E6;
    LL f[M] = {0, 1};
    void init() {
        static bool vis[M];
        static LL pr[M], p_sz, d;
        FOR (i, 2, M) {
            if (!vis[i]) { pr[p_sz++] = i; f[i] = -1; }
            FOR (j, 0, p_sz) {
                if ((d = pr[j] * i) >= M) break;
                vis[d] = 1;
                if (i % pr[j] == 0) {
                    f[d] = 0;
                    break;
                } else f[d] = -f[i];
            }
        }
        FOR (i, 2, M) f[i] += f[i - 1];
    }
    inline LL s_fg(LL n) { return 1; }
    inline LL s_g(LL n) { return n; }

    LL N, rd[M];
    bool vis[M];
    LL go(LL n) {
        if (n < M) return f[n];
        LL id = N / n;
        if (vis[id]) return rd[id];
        vis[id] = true;
        LL& ret = rd[id] = s_fg(n);
        for (LL l = 2, v, r; l <= n; l = r + 1) {
            v = n / l; r = n / v;
            ret -= (s_g(r) - s_g(l - 1)) * go(v);
        }
        return ret;
    }
    LL solve(LL n) {
        N = n;
        memset(vis, 0, sizeof vis);
        return go(n);
    }
}

vector<LL> fac;
const int M = 1 << 11;

inline LL mumu(LL x) { return __builtin_popcountll(x) & 1 ? -1 : 1; }

LL go(LL n, LL m, LL mm) { // m = mm, n = N / nn
//    dbg(n, m, mm);
    if (n == 0) return 0;
    if (m == 1) return dujiao::go(n);

    LL ret = 0;

    auto fuck = [&](LL d, LL s) {
        ret += go(n / d, d, s) * mumu(s);
    };

    for (LL s = (mm - 1) & mm; s; s = (s - 1) & mm) {
        LL d = 1;
        FOR (i, 0, fac.size())
            if ((1 << i) & s) d *= fac[i];
        fuck(d, s);
    }
    fuck(m, mm);
    fuck(1, 0);
    dbg(n, m, mm, ret * mumu(mm));
    return mumu(mm) * ret;
}


int main() {
    dujiao::init();
    LL m, n, _m; cin >> n >> _m; m = _m;
    dujiao::solve(n);
    FOR (i, 2, LL(sqrt(m + 0.5)) + 1) {
        if (m % i == 0) {
            if (m % (i * i) == 0) { puts("0"); return 0; }
            fac.push_back(i);
            while (m % i == 0) m /= i;
        }
    }
    if (m > 1) fac.push_back(m);
    dbg(fac);
    cout << go(n, _m, (1 << fac.size()) - 1) << endl;
}
