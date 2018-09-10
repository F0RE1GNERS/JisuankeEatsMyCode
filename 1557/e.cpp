#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[31;1m" << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
const int N = 70;
int n;
struct Mat {
    static const LL M = N;
    LL v[M][M];
    Mat() { memset(v, 0, sizeof v); }
    LL* operator [] (LL x) { return v[x]; }
    const LL* operator [] (LL x) const { return v[x]; }
    Mat operator * (const Mat& B) {
        const Mat& A = *this;
        Mat ret;
        FOR (i, 0, n)
            FOR (j, 0, n)
                FOR (k, 0, n)
                    if (A[i][k] != 0 && B[k][j] != 0)
                        ret[i][j] = max(ret[i][j], A[i][k] + B[k][j]);
        FOR (i, 0, n) FOR (j, 0, n) ret[i][j] = max(ret[i][j], max(A[i][j], B[i][j]));
        return ret;
    }
    Mat operator + (const Mat& B) {
        const Mat& A = *this;
        Mat ret;
        FOR (i, 0, n)
            FOR (j, 0, n)
                ret[i][j] = max(A[i][j], B[i][j]);
        return ret;
    }
};

bool G[N][N];
LL v[N];
Mat I, A, rA;
int main() {
    int m; LL K, T;  cin >> n >> m >> K >> T;
    --T; --K; K -= T;
    FOR (_, 0, m) {
        int u, v; scanf("%d%d", &u, &v);
        G[--u][--v] = true;
    }
    FOR (i, 0, n) scanf("%lld", &v[i]);
    FOR (i, 0, n) I[i][i] = v[i];
    FOR (i, 0, n) FOR (j, 0, n)
        if (G[i][j]) {
            A[i][j] = v[j];
            rA[i][j] = v[i];
        }
    Mat AA = A, R = I;
    for (; T; T >>= 1, AA = AA * AA) if (T & 1) R = R * AA;
    FOR (i, 0, n) FOR (j, 0, n) R[i][j] *= 2;

    int lim = 0;
    while ((1LL << (lim + 1)) - 1 <= K) ++lim;
    K -= (1LL << lim) - 1;

    FOR (i, 0, lim) {
        if (K & (1 << i)) R = rA * R + R * A;
        R = rA * R + R * A;
        rA = rA * rA; A = A * A;
    }

    LL ans = 0;
    FOR (i, 0, n) FOR (j, 0, n) ans = max(ans, R[i][j]);
    cout << ans << endl;
} 
