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

struct P {
    LL min, max;
};

P go(const P& x, const LL &y, char op) {
    if (op == '+') return {x.min + y, x.max + y};
    if (op == '-') return {x.min - y, x.max - y};
    if (op == '*') {
        LL ax = x.min * y;
        LL bx = x.max * y;
        return {min(ax, bx), max(ax, bx)};
    }
    if (op == '/') {
        LL ax = x.min / y;
        LL bx = x.max / y;
        return {min(ax, bx), max(ax, bx)};
    }
    assert (0);
}

const int N = 1E3 + 100;
const int K = 7;
int n, m, k;
int a[N]; string f;
P dp[N][K]; int vis[N][N];

void update(P &x, const P& y) {
    LL a = y.min, b = y.max;
    x.min = min(x.min, a);
    x.max = max(x.max, b);
}

int main() {
    #ifdef zerol
    freopen("B.in", "r", stdin);
    #endif // zerol
    int T; cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        FOR (i, 0, n) scanf("%d", a + i);
        cin >> f;
        memset(vis, 0, sizeof vis);
        memset(dp, 0, sizeof dp);
        dp[0][0] = {k, k};
        vis[0][0] = 1;
        FOR (i, 0, n) {
            FOR (j, 0, m + 1) {
                if (!vis[i][j]) continue;

                if (!vis[i + 1][j]) {
                    vis[i + 1][j] = 1;
                    dp[i + 1][j] = dp[i][j];
                } else { update(dp[i + 1][j], dp[i][j]); }

                if (j < m) {
                    if (!vis[i + 1][j + 1]) {
                        vis[i + 1][j + 1] = 1;
                        dp[i + 1][j + 1] = go(dp[i][j], a[i], f[j]);
                    } else { update(dp[i + 1][j + 1], go(dp[i][j], a[i], f[j])); }
                }
            }
        }
        cout << dp[n][m].max << endl;
    }
}
