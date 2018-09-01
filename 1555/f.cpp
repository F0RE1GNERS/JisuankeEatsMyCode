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

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }
const LL MOD = 998244353;

const int N = 1E5 + 100;
namespace lct {
    extern struct P *const null;
    const int M = N;
    struct P {
        P *fa, *ls, *rs;
        int sz, _sz;
        bool rev;

        bool has_fa() { return fa->ls == this || fa->rs == this; }
        bool d() { return fa->ls == this; }
        P*& c(bool x) { return x ? ls : rs; }
        void do_rev() {
            if (this == null) return;
            rev ^= 1;
            swap(ls, rs);
        }
        P* up() {
            sz = ls->sz + rs->sz + _sz + 1;
            return this;
        }
        void down() {
            if (rev) {
                rev = 0;
                ls->do_rev(); rs->do_rev();
            }
        }
        void all_down() { if (has_fa()) fa->all_down(); down(); }
    } *const null = new P{0, 0, 0, 0, 0, 0}, pool[M], *pit = pool;

    void rot(P* o) {
        bool dd = o->d();
        P *f = o->fa, *t = o->c(!dd);
        if (f->has_fa()) f->fa->c(f->d()) = o; o->fa = f->fa;
        if (t != null) t->fa = f; f->c(dd) = t;
        o->c(!dd) = f->up(); f->fa = o;
    }
    void splay(P* o) {
        o->all_down();
        while (o->has_fa()) {
            if (o->fa->has_fa())
                rot(o->d() ^ o->fa->d() ? o : o->fa);
            rot(o);
        }
        o->up();
    }
    void access(P* u, P* v = null) {
        if (u == null) return;
        splay(u);
        u->_sz += u->rs->sz - v->sz;
        u->rs = v;
        access(u->up()->fa, u);
    }
    void make_root(P* o) {
        access(o); splay(o); o->do_rev();
    }
    void split(P* o, P* u) {
        make_root(o); access(u); splay(u);
    }
    void link(P* u, P* v) {
        make_root(u); make_root(v);
        u->fa = v; v->_sz += u->sz;
        v->up();
    }
    void cut(P* u, P* v) {
        split(u, v); // assert(u->fa == v && v->ls == u);
        u->fa = v->ls = null; v->up();
    }
    bool adj(P* u, P* v) {
        split(u, v);
        return v->ls == u && u->ls == null && u->rs == null;
    }
    bool linked(P* u, P* v) {
        split(u, v);
        return u == v || u->fa != null;
    }
}

using namespace lct;
P* G[N];
int d[N];
int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    int n, Qn; cin >> n >> Qn;
    FOR (i, 1, n + 1) {
        G[i] = pit++;
        G[i]->ls = G[i]->rs = G[i]->fa = null;
    }
    FOR (_, 1, n) {
        int u, v; scanf("%d%d", &u, &v);
        link(G[u], G[v]); ++d[u]; ++d[v];
    }
    while (Qn--) {
        int tp; scanf("%d", &tp);
        if (tp == 1) {
            int u, v; scanf("%d%d", &u, &v);
            if (linked(G[u], G[v])) puts("-1");
            else {
                ++d[u]; ++d[v];
                link(G[u], G[v]);
            }
        } else if (tp == 2) {
            int u, v; scanf("%d%d", &u, &v);
            if (!linked(G[u], G[v])) puts("-1");
            else {

                if (u == v) puts("-1");
                else {
                    make_root(G[u]);
                    access(G[v]); splay(G[v]);
                    P* nxt = G[v]->ls;
                    while (nxt->rs != null) {
                        nxt = nxt->rs;
                        nxt->down();
                    }
                    assert(adj(nxt, G[v]));
                    --d[v]; --d[nxt - pool + 1];
//                    assert(G[nxt - pool + 1] == nxt);
                    cut(G[v], nxt);
                }
            }
        } else {
            int x; scanf("%d", &x);
            make_root(G[x]);
            dbg(x, G[x]->sz, d[x]);
            if (G[x]->sz == 1) puts("0");
            else {
                LL ans = (G[x]->sz - 1) * get_inv(d[x], MOD) * 2 % MOD;
                printf("%lld\n", ans);
            }
        }

    }
//    FOR (i, 1, n + 1) {
//        make_root(G[i]); dbg(i, G[i]->sz);
//    }
}
