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
const int M = 10000 + 5, N = 200 + 5, INF = 1E9;
const double eps = 1e-6;
namespace lp {
    int n, m;
    double a[M][N], b[M], c[N], v;

    void pivot(int l, int e) {
        b[l] /= a[l][e];
        FOR (j, 0, n) if (j != e) a[l][j] /= a[l][e];
        a[l][e] = 1 / a[l][e];

        FOR (i, 0, m)
            if (i != l && fabs(a[i][e]) > 0) {
                b[i] -= a[i][e] * b[l];
                FOR (j, 0, n)
                    if (j != e) a[i][j] -= a[i][e] * a[l][j];
                a[i][e] = -a[i][e] * a[l][e];
            }
        v += c[e] * b[l];
        FOR (j, 0, n) if (j != e) c[j] -= c[e] * a[l][j];
        c[e] = -c[e] * a[l][e];
    }
    double simplex() {
        while (1) {
            int e = -1, l = -1;
            FOR (i, 0, n) if (c[i] > eps) { e = i; break; }
            if (e == -1) return v;
            double t = INF;
            FOR (i, 0, m)
                if (a[i][e] > eps && t > b[i] / a[i][e]) {
                    t = b[i] / a[i][e];
                    l = i;
                }
            if (l == -1) return INF;
            pivot(l, e);
        }
    }
}

struct P { int l, r, w; };
P a[N];
int main() {
    int T; cin >> T;
    while (T--) {
        int n, k, m; cin >> n >> k >> m;
        vector<int> t;
        FOR (i, 0, m) {
            scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].w);
            t.push_back(a[i].l); t.push_back(++a[i].r);
        }
        sort(t.begin(), t.end());
        t.erase(unique(t.begin(), t.end()), t.end());
        auto id = [&](int x)->int { return lower_bound(t.begin(), t.end(), x) - t.begin(); };
        FOR (i, 0, m) a[i].l = id(a[i].l), a[i].r = id(a[i].r);


        lp::v = 0; lp::n = m;
        FOR (i, 0, m) lp::c[i] = a[i].w;
        int p = 0;
        FOR (i, 0, m) {
            memset(lp::a[p], 0, sizeof lp::a[p]);
            lp::a[p][i] = 1; lp::b[p] = 1;
            p++;
        }
        FOR (i, 0, (int)t.size() - 1) {
            memset(lp::a[p], 0, sizeof lp::a[p]);
            int ll = i, rr = i + 1;
            FOR (j, 0, m) if (a[j].l <= ll && a[j].r >= rr) lp::a[p][j] = 1;
            lp::b[p] = k;
            p++;
        }
        lp::m = p;
        printf("%lld\n", llround(lp::simplex()));
    }
}
