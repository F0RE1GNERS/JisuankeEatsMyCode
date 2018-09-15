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

const int N = 1e4+10;
const int MOD = 1e9+7;

int a[N];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, q; scanf("%d%d", &n, &q);
        memset(a, 0, sizeof(a));
        a[0] = 1;
        FOR(i, 0, n) {
            int v, c; scanf("%d%d", &v, &c); c = v << c;
            FOR(i, 0, N-v) a[i+v] = (a[i+v]+a[i])%MOD;
            FORD(i, N-c-1, -1) a[i+c] = (a[i+c]-a[i]+MOD)%MOD;
        }
        while(q--) {
            int t; scanf("%d", &t);
            printf("%d\n", a[t]);
        }
    }
}
