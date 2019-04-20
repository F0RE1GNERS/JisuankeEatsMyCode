#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
#else
#define dbg(...)
#endif // zerol
void err() { cout << "\033[39;0m" << endl; }
template<typename T, typename... A>
void err(T a, A... x) { cout << a << ' '; err(x...); }
// ----------------------------------------------------------------------------------------

const int N = 5e5+10;
const int M = N;

struct RMQ {
    LL f[22][M], g[22][M];
    inline LL highbit(LL x) { return 31 - __builtin_clz(x); }
    void init(LL* v, LL n) {
        FOR (i, 0, n) f[0][i] = g[0][i] = v[i];
        FOR (x, 1, highbit(n) + 1)
            FOR (i, 0, n - (1 << x) + 1)
                f[x][i] = min(f[x - 1][i], f[x - 1][i + (1 << (x - 1))]),
                g[x][i] = max(g[x - 1][i], g[x - 1][i + (1 << (x - 1))]);
    }
    LL get_min(LL l, LL r) {
        assert(l <= r);
        LL t = highbit(r - l + 1);
        return min(f[t][l], f[t][r - (1 << t) + 1]);
    }

    LL get_max(LL l, LL r) {
        assert(l <= r);
        LL t = highbit(r - l + 1);
        return max(g[t][l], g[t][r - (1 << t) + 1]);
    }
} sum;

int fa[N]; int Fa(int x) { return fa[x] == x? x: (fa[x] = Fa(fa[x])); }
int fb[N]; int Fb(int x) { return fb[x] == x? x: (fb[x] = Fb(fb[x])); }

LL a[N], b[N];

pair<int, int> c[N];

int main() {
    int n; scanf("%d", &n);
    a[n+1] = a[0] = -1e6;
    FOR(i, 1, n+1) scanf("%lld", a+i), b[i] = b[i-1]+a[i], c[i] = { (int)a[i], i};
    sum.init(b, n+1);
    iota(fa, fa+n+2, 0);
    iota(fb, fb+n+2, 0);
    sort(c+1, c+n+1, greater<pair<int, int>>());
    LL ans = -1e18;
    FOR(i, 1, n+1) {
        int p = c[i].second;
        if(a[p+1]>=a[p]) {
            fa[Fa(p)] = Fa(p+1);
            fb[Fb(p+1)] = Fb(p);
        }
        if(a[p-1]>=a[p]) {
            fa[Fa(p-1)] = Fa(p);
            fb[Fb(p)] = Fb(p-1);
        }
        int l = Fb(p), r = Fa(p);
        LL ret;
        if(c[i].first<0) {
            ret = (sum.get_min(p, r)-sum.get_max(l-1, p-1))*c[i].first;
            dbg(sum.get_min(p, r), sum.get_max(l-1, p-1));
        } else {
            ret = (sum.get_max(p, r)-sum.get_min(l-1, p-1))*c[i].first;
            dbg(sum.get_max(p, r), sum.get_min(l-1, p-1));
        }
        dbg(l, p, r, ret);
        if(ret>ans) ans = ret;
    }
    printf("%lld\n", ans);
    return 0;
}