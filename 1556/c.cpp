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

const LL p_max = 1E5 + 100;
LL mu[p_max] = {-1, 1};
void get_mu() {
    static bool vis[p_max];
    static LL prime[p_max], p_sz, d;
    mu[1] = 1;
    FOR (i, 2, p_max) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            mu[i] = -1;
        }
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                mu[d] = 0;
                break;
            }
            else mu[d] = -mu[i];
        }
    }
}

__int128 n, p;
__int128 S3(__int128 x) {
    __int128 r = x * (x + 1) / 2 % p;
    return r * r % p;
}
__int128 S2(__int128 x) { return x * (x + 1) / 2 * (2 * x + 1) / 3 % p; }
__int128 dk(__int128 d, int k) {
    __int128 ret = 1;
    FOR (_, 0, k) ret = ret * d % p;
    return ret;
}

int main() {
    get_mu();
    LL _n, _p;
    while (cin >> _n >> _p) {

        n = _n; p = _p;
        __int128 ans = 0;
        FOR (d, 1, (__int128)sqrt(n + 0.5) + 1) {
            __int128 t = n / d / d;
            ans += mu[d] * (S2(t) % p * dk(d, 4) % p * (n + 1) % p
                   - dk(d, 6) * S3(t) % p);
        }
        ans = ans % p;
        dbg(LL(ans));
        LL Ans = ans;
        cout << (Ans % _p + _p) % _p << endl;
    }
}
