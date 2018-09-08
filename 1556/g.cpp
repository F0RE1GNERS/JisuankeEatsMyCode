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
const LL MOD = 1E9 + 7;

const LL p_max = 1E5 + 100;
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


LL factor[30], f_sz;
void get_factor(LL x) {
    f_sz = 0;
    LL t = sqrt(x + 0.5);
    for (LL i = 0; pr[i] <= t; ++i)
        if (x % pr[i] == 0) {
            factor[f_sz++] = pr[i];
            while (x % pr[i] == 0) x /= pr[i];
        }
    if (x > 1) factor[f_sz++] = x;
}


LL s1(LL x) { return x * (x + 1) / 2 % MOD; }
LL s2(LL x) {
    __int128 t = x;
    return t * (t + 1) / 2 * (2 * t + 1) / 3 % MOD;
}

LL ans;
void dfs(int cur, LL s, LL sgn, LL k) {
    if (cur == f_sz) {
//        dbg(s, sgn, s1(s), s2(s), sgn * (s1(s) + s2(s)));
        ans = (ans + sgn * (k * s1(s) % MOD + s2(s) * k % MOD * k % MOD)) % MOD;
        return;
    }
    dfs(cur + 1, s, sgn, k);
    dfs(cur + 1, s / factor[cur], -sgn, k * factor[cur]);
}

int main() {
    get_prime();
    LL n, m;
    while (~scanf("%lld%lld", &n, &m)) {
        get_factor(m);
        ans = 0;
        dfs(0, n, 1, 1);
        printf("%lld\n", (ans % MOD + MOD) % MOD);
    }
}
