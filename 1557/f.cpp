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
typedef pair<int, int> P;

int n, m;
map<P, int> counter;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        m = 0; int ans = 0;
        counter.clear();
        FOR (i, 0, n) {
            int k; scanf("%d", &k);
            map<P, int> new_counter;
            while (k--) {
                int x, y, t; scanf("%d%d", &x, &y);
                new_counter[{x, y}] = t = counter[{x, y}] + 1;
                ans = max(ans, t);
            }
            counter.swap(new_counter);
        }
        cout << ans << endl;
    }
}
