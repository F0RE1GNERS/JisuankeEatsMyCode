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

typedef pair<int, int> P;
const int N = 110;
int n, m, b;
vector<int> nxt[N];
int h[N];
LL res;

int main() {
    int T; cin >> T; int cas = 0;
    while (T--) {
        cin >> n >> m >> b;
        FOR (i, 1, m + 1) nxt[i].clear();
        FOR (i, 0, b) {
            int x, y; cin >> x >> y;
            nxt[y].push_back(x);
        }
        FOR (i, 1, m + 1) sort(nxt[i].begin(), nxt[i].end());
        memset(h, 0, sizeof h);
        res = 0;
        FORD (col, n, 0) {
            FOR (i, 1, m + 1) h[i]++;
            FOR (i, 1, m + 1) if (!nxt[i].empty() && nxt[i].back() == col) {
                h[i] = 0; nxt[i].pop_back();
            }
            FOR (i, 1, m + 1) dbg(col, i, h[i]);
            stack<P> s; s.emplace(0, m + 1);
            LL ans = 0;
            FORD (i, m, 0) {
                while (h[i] < s.top().first) {
                    int x1 = s.top().second, y1 = s.top().first; s.pop();
                    int x2 = s.top().second;
                    ans -= (x2 - x1) * y1;
                }
                int x1 = i, x2 = s.top().second;
                s.emplace(h[i], i);
                ans += h[i] * (x2 - x1);
                dbg(col, i, ans);
                res += ans;
            }
        }
        printf("Case #%d: ", ++cas);
        cout << res << endl;
    }
}
