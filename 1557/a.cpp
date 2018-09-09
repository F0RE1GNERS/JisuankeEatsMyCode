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

const int N = 1E6 + 100, MOD = 1E9 + 7;

int n, k, all, ans;
int first;

void solve(int dep, int last) {
    if (dep == n) { if (all ^ last ^ first) ans++; return; }
    FOR (i, 0, 1 << k) {
        if (all ^ i ^ last)
            solve(dep + 1, i);
    }
}

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }

LL invf[N], fac[N];
void fac_inv_init(LL n, LL p) {
    fac[0] = 1;
    FOR (i, 1, n)
        fac[i] = i * fac[i - 1] % p;
    invf[n - 1] = bin(fac[n - 1], p - 2, p);
    FORD (i, n - 2, -1)
        invf[i] = invf[i + 1] * (i + 1) % p;
}
inline LL C(LL n, LL m) { // n >= m >= 0
    return n < m || m < 0 ? 0 : fac[n] * invf[m] % MOD * invf[n - m] % MOD;
}

int main() {
    int T; cin >> T;
    LL n, k;
    fac_inv_init(N, MOD);
    while (T--) {
        cin >> n >> k;
        LL ans = 0;
        FOR (i, 0, n) {
            LL p = C(n, i) * bin(2, k * (n - i) % (MOD - 1), MOD) % MOD;
            if (i % 2 == 0) (ans += p) %= MOD;
            else (ans += MOD - p) %= MOD;
        }
        if (n % 2 == 0) (ans += bin(2, k, MOD)) %= MOD;
        cout << ans << endl;
    }
}
