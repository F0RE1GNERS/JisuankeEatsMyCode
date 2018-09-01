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
namespace min25 {
    const int M = 1E6 + 100;
    LL B, N;

    // g(x)
    inline LL ph(LL x) { return 1; }
    // Sum[g(i),{x,2,x}]
    inline LL psh(LL x) {
        return x * 1 - 1;
    }
    // f(pp=p^k)
    inline LL fpk(LL p, LL e, LL pp) {
        if (e == 1) return 2;
        if (e == 2) return 1;
        return 0;
    }
    // f(p) = fgh(g(p), h(p))
    inline LL fgh(LL h) { return h * 2; }

    LL pr[M], pc, sh[M];
    void get_prime(LL n) {
        static bool vis[M]; pc = 0;
        FOR (i, 2, n + 1) {
            if (!vis[i]) {
                pr[pc++] = i;
                sh[pc] = sh[pc - 1] + ph(i);
            }
            FOR (j, 0, pc) {
                if (pr[j] * i > n) break;
                vis[pr[j] * i] = 1;
                if (i % pr[j] == 0) break;
            }
        }
    }

    LL w[M];
    LL id1[M], id2[M], h[M];
    inline LL id(LL x) { return x <= B ? id1[x] : id2[N / x]; }

    LL go(LL x, LL k) {
        if (x <= 1 || (k >= 0 && pr[k] > x)) return 0;
        LL t = id(x);
        LL ans = fgh(h[t] - sh[k + 1]);
        FOR (i, k + 1, pc) {
            LL p = pr[i];
            if (p * p > x) break;
            ans -= fgh(ph(p));
            for (LL pp = p, e = 1; pp <= x; ++e, pp = pp * p)
                ans += fpk(p, e, pp) * (1 + go(x / pp, i));
        }
        return ans;
    }

    LL solve(LL _N) {
        N = _N;
        B = sqrt(N + 0.5);
        get_prime(B);
        int sz = 0;
        for (LL l = 1, v, r; l <= N; l = r + 1) {
            v = N / l; r = N / v;
            w[sz] = v; h[sz] = psh(v);
            if (v <= B) id1[v] = sz; else id2[r] = sz;
            sz++;
        }
        FOR (k, 0, pc) {
            LL p = pr[k];
            FOR (i, 0, sz) {
                LL v = w[i]; if (p * p > v) break;
                LL t = id(v / p);
                h[i] = h[i] - (h[t] - sh[k]) * ph(p);
            }
        }
        return go(N, -1) + 1;
    }
}

int main() {
    int T; cin >> T;
    while (T--) {
        LL n; cin >> n;
        cout << min25::solve(n) << endl;
    }
}
