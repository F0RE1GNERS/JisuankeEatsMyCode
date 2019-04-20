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
using ULL = unsigned int;
const ULL M = 1E7 + 10;
ULL mu[M];
ULL phi[M];
void get_hahahaha() {
    mu[1] = 1; phi[1] = 1;
    static bool vis[M];
    static ULL prime[M], p_sz, d;
    FOR (i, 2, M) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (ULL j = 0; j < p_sz && (d = i * prime[j]) < M; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                phi[d] = phi[i] * prime[j];
                mu[d] = 0;
                break;
            }
            else {
                mu[d] = -mu[i];
                phi[d] = phi[i] * (prime[j] - 1);
            }
        }
    }
}


ULL f(ULL i) {
    return (i * i * (i + 1) * i * (i + 1) * (2 * i + 1));
}

ULL g(ULL n) {
    ULL ret = 0;
    for (ULL l = 1, v, r; l <= n; l = r + 1) {
        v = n / l; r = n / v;
        ret += f(v) * (mu[r] - mu[l - 1]);
    }
    return ret;
}

ULL mem[M];
ULL ZZ = 23333333ULL;
ULL get_g(ULL x) {
    if (x < M) {
        if (mem[x] == ZZ) mem[x] = g(x);
        return mem[x];
    }
    return g(x);
}


const ULL MMM = 1 << 30;
int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    get_hahahaha();
    FOR (i, 1, M) {
        phi[i] *= i * i * i;
        mu[i] *= i * i * i;
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
        mem[i] = ZZ;
    }
    dbg("!");
    int T; cin >> T;
    while (T--) {
        ULL n; cin >> n;
        dbg(n);
        ULL ans = 0;
        for (ULL l = 1, v, r; l <= n; l = r + 1) {
            v = n / l; r = n / v;
            ans += get_g(v) * (phi[r] - phi[l - 1]);
        }
        cout << ans / 4 * 715827883ULL % MMM << endl;
    }
}