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
using uLL = unsigned long long;
const int N = 10;
int a[N][N], b[N][N], c[N][N];
uLL f[N][N];
int n, m, mm;

void go() {
    static uLL ff[N][N]; memset(ff, 0, sizeof ff);
    int mm = (m - 1) / 2;
    FOR (i, 1, n + 1)
        FOR (j, 1, n + 1)
            FOR (x, i - mm, i + mm + 1)
                FOR (y, j - mm, j + mm + 1)
                    if (x > 0 && y > 0 && x <= n && y <= n) {
                        if (b[x - i + mm + 1][y - j + mm + 1])
                            ff[i][j] ^= f[x][y];
                    }
    swap(f, ff);
}

void fuck() {
    static uLL ff[N][N]; memset(ff, 0, sizeof ff);
    FOR (i, 1, n + 1)
        FOR (j, 1, n + 1)
            FOR (x, 1, n + 1)
                FOR (y, 1, n + 1)
                    if (f[x][y] & (1ull << c[i][j]))
                        ff[x][y] ^= f[i][j];
    swap(f, ff);
}

uLL encode() {
    uLL r = 0;
    FOR (i, 1, n + 1) FOR (j, 1, n + 1) if (a[i][j]) r |= 1ull << c[i][j];
    return r;
}

void shit() {
    uLL t = encode();
    FOR (i, 1, n + 1)
        FOR (j, 1, n + 1)
            a[i][j] = __builtin_popcountll(f[i][j] & t) & 1;
}




int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    int T; cin >> T;
    while (T--) {
        int K; cin >> n >> m >> K; mm = (m - 1) / 2;
        FOR (i, 1, n + 1) FOR (j, 1, n + 1) scanf("%d", &a[i][j]), a[i][j] &= 1;
        FOR (i, 1, m + 1) FOR (j, 1, m + 1) scanf("%d", &b[i][j]), b[i][j] &= 1;
        int p = 0; FOR (i, 1, n + 1) FOR (j, 1, n + 1) c[i][j] = p++;
        FOR (i, 1, n + 1) FOR (j, 1, n + 1) f[i][j] = 1ull << c[i][j];
        go();
        for (; K; K >>= 1, fuck()) if (K & 1) shit();
        int ans = 0; FOR (i, 1, n + 1) FOR (j, 1, n + 1) ans += a[i][j];
        cout << ans << endl;
    }
}
