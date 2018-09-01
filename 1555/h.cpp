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
const int M = 6E5 + 100;
const LL R = (1LL << 31) - 1;

LL transform(int x) {
    LL ret = 0;
    for(int i = 0; i<31; ++i) {
        ret = (ret<<1)+(x&1);
        x>>=1;
    }
    return ret;
}
namespace tree {
#define mid ((l + r) >> 1)
#define lson l, mid
#define rson mid + 1, r
    const int MAGIC = M * 64;
    struct P {
        int sum, ls, rs;
    } tr[MAGIC] = {{0, 0, 0}};
    int sz = 1;
    int N(int sum, int ls, int rs) {
        if (sz == MAGIC) assert(0);
        tr[sz] = {sum, ls, rs};
        return sz++;
    }
    int ins(int o, LL x, LL l = 0, LL r = R) {
        if (x < l || x > r) return o;
        const P& t = tr[o];
//        dbg(t.sum + v);
        if (l == r) return N(t.sum + 1, 0, 0);
        return N(t.sum + 1, ins(t.ls, x, lson), ins(t.rs, x, rson));
    }
    int query(int o, LL x, int k) {
        const P& t = tr[o];
        if (k == 0) return t.sum;
        LL xx = x % 2; x /= 2; --k;
        if (xx == 0) return query(t.ls, x, k);
        else return query(t.rs, x, k);
    }
    int merge(int p, int q) {
        if (p == 0 || q == 0) return p ^ q;
        return N(tr[p].sum + tr[q].sum,
                merge(tr[p].ls, tr[q].ls),
                merge(tr[p].rs, tr[q].rs));
    }
    void rev(int o) {
        if (!o) return;
        swap(tr[o].ls, tr[o].rs);
        rev(tr[o].ls);
    }
}
using namespace tree;

int fa[M];
int findset(int x) { return fa[x] == -1 ? x : fa[x] = findset(fa[x]); }
int rt[M];


int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    dbg(R, transform(1));
    memset(fa, -1, sizeof fa);
    int n, Qn; cin >> n >> Qn;
    FOR (i, 1, n + 1) {
        int t; scanf("%d", &t);
        rt[i] = ins(0, transform(t));
        dbg(rt[i]);
        dbg(tr[rt[i]].sum);
    }
    while (Qn--) {
        int tp; scanf("%d", &tp);
        dbg(tp);
        if (tp == 1) {
            int u, v; scanf("%d%d", &u, &v);
            int fu = findset(u), fv = findset(v);
            if (fu != fv) {
                fa[fu] = fv;
                rt[fv] = merge(rt[fv], rt[fu]);
                dbg(tr[rt[fv]].sum);
            }
        } else if (tp == 2) {
            int u; scanf("%d", &u);
            rev(rt[findset(u)]);
        } else if (tp == 3) {
            int u, k, x; scanf("%d%d%d", &u, &k, &x);
            printf("%d\n", query(rt[findset(u)], x, k));
        }
    }
}
