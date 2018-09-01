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
// -----------------------------------------------------------------------------

const LL NINF = -1E18;
const int N = 22;
int n, s[N];
LL a[N], b[N];
LL f[1 << N], vis[1 << N];

LL go(int state) {
    if (vis[state]) return f[state];
    vis[state] = 1;
    // dbg(state);
    int clk = __builtin_popcount(state);
    FOR (i, 0, n) {
        if ((1 << i) & state) {
            int previous = state & (~(1 << i));
            if ((previous & s[i]) == s[i])
                f[state] = max(f[state], go(state & (~(1 << i))) + a[i] * clk + b[i]);
        }
    }
    return f[state];
}

int main() {
    cin >> n;
    FOR (i, 1, 1 << n) f[i] = NINF;
    FOR (i, 0, n) {
        int sz; cin >> a[i] >> b[i] >> sz;
        while (sz--) {
            int k; cin >> k;
            s[i] |= (1 << (k - 1));
        }
    }
    LL ans = 0;
    FOR (i, 0, 1 << n) ans = max(ans, go(i));
    cout << ans << endl;
}
