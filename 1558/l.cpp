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

const int M = 9;
const int MOD = 1e9+7;

struct Matrix {
    Matrix() { memset(dat, 0, sizeof(dat)); }
    LL dat[M][M];
    void multi(const Matrix& q) {
        LL tmp[M][M];
        memset(tmp, 0, sizeof(tmp));
        FOR(k, 0, M)
            FOR(i, 0, M)
                FOR(j, 0, M)
                    tmp[i][j]=(tmp[i][j]+dat[i][k]*q.dat[k][j])%MOD;
        FOR(i, 0, M)
            FOR(j, 0, M) dat[i][j] = tmp[i][j];
    }
};

int main() {
    Matrix trans;
    FOR(i, 0, 3)
        FOR(j, 0, 3)
            FOR(k, 0, 3) {
                if(i==j && j==k) continue;
                if(j==1 && i+j+k==3) continue;
                if(i==1 && k==1) continue;
                ++trans.dat[j*3+k][i*3+j];
            }
    int T; cin >> T;
    while (T--) {
        LL n; cin >>n;
        Matrix left = Matrix(), right = trans;
        if(n==1) puts("3");
        else if(n==2) puts("9");
        else {
            FOR(i, 0, M) left.dat[0][i] = 1;
            n-=2;
            while(n) {
                if(n&1) left.multi(right);
                right.multi(right);
                n>>=1;
            }
            LL ans = 0;
            FOR(i, 0, M) ans+=left.dat[0][i];
            cout << ans%MOD << endl;
        }
    }
}
