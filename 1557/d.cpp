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
const LL MOD = 998244353;


const LL p_max = 1E6 + 100;
LL pr[p_max], p_sz;
void get_prime() {
    static bool vis[p_max];
    FOR (i, 2, p_max) {
        if (!vis[i]) pr[p_sz++] = i;
        FOR (j, 0, p_sz) {
            if (pr[j] * i >= p_max) break;
            vis[pr[j] * i] = 1;
            if (i % pr[j] == 0) break;
        }
    }
}

LL factor[30], f_sz, factor_exp[30];
void get_factor(LL x) {
    f_sz = 0;
    LL t = sqrt(x + 0.5);
    for (LL i = 0; pr[i] <= t; ++i)
        if (x % pr[i] == 0) {
            factor_exp[f_sz] = 0;
            while (x % pr[i] == 0) {
                x /= pr[i];
                ++factor_exp[f_sz];
            }
            factor[f_sz++] = pr[i];
        }
    if (x > 1) {
        factor_exp[f_sz] = 1;
        factor[f_sz++] = x;
    }
}

inline bool check(LL x) { return binary_search(factor, factor + f_sz, x); }

namespace min25 {
    const int M = 1E6 + 100;
    LL B, N;

    // g(x)
    inline LL pg(LL x) { return 1; }
    inline LL pgg(LL x) { return 1 - check(x); }
    // Sum[g(i),{x,2,x}]
    inline LL psg(LL x) {
        return x - 1;
    }
    // f(p) = fgh(g(p), h(p))
    inline LL fgh(LL g) { return -g; }
    inline LL fpk(LL p, LL e, LL pp) { return e == 1 && !check(p) ? -1 : 0; }

    LL pr[M], pc, sg[M], sgg[M];
    void get_prime(LL n) {
        static bool vis[M]; pc = 0;
        FOR (i, 2, n + 1) {
            if (!vis[i]) {
                pr[pc++] = i;
                sg[pc] = (sg[pc - 1] + pg(i));
                sgg[pc] = (sgg[pc - 1] + pgg(i));
            }
            FOR (j, 0, pc) {
                if (pr[j] * i > n) break;
                vis[pr[j] * i] = 1;
                if (i % pr[j] == 0) break;
            }
        }
    }

    LL w[M];
    LL id1[M], id2[M], g[M];
    inline LL id(LL x) { return x <= B ? id1[x] : id2[N / x]; }

    LL go(LL x, LL k) {
        if (x <= 1 || (k >= 0 && pr[k] > x)) return 0;
        LL t = id(x);
        LL ans = fgh((g[t] - sgg[k + 1]));
        FOR (i, k + 1, pc) {
            LL p = pr[i];
            if (p * p > x) break;
            ans -= fgh(pgg(p));
            for (LL pp = p, e = 1; pp <= x; ++e, pp = pp * p)
                ans += fpk(p, e, pp) * (1 + go(x / pp, i));
        }
        return ans;
    }

    LL solve(LL _N) {
//        dbg(pg(2), fpk(3, 1, 2), fpk(3, 2, 4));
        N = _N;
        B = sqrt(N + 0.5);
        get_prime(B);
        int sz = 0;
        for (LL l = 1, v, r; l <= N; l = r + 1) {
            v = N / l; r = N / v;
            w[sz] = v; g[sz] = psg(v);
//            dbg(v, g[sz]);
            if (v <= B) id1[v] = sz; else id2[r] = sz;
            sz++;
        }
        FOR (k, 0, pc) {
            LL p = pr[k];
            FOR (i, 0, sz) {
                LL v = w[i]; if (p * p > v) break;
                LL t = id(v / p);
                g[i] = (g[i] - (g[t] - sg[k]) * pg(p));
            }
        }
        FOR (i, 0, sz) {
//            dbg(i, g[i]);
            g[i] = g[i] - LL(upper_bound(factor, factor + f_sz, w[i]) - factor);
            dbg(i, w[i], g[i]);
        }
        return go(N, -1) + 1;
    }
}




int main() {
    get_prime();
    LL m, n; cin >> m >> n;
    get_factor(n);
    FOR (i, 0, f_sz)
        if (factor_exp[i] > 1) { puts("0"); return 0; }

//    FOR (i, 1, 11) dbg(i, min25::solve(i));
//    dbg(min25::solve(10));
    LL ans = min25::solve(m) * (f_sz & 1 ? -1 : 1);
    cout << ans << endl;
}
