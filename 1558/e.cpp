#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "DEBUG: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)

const int N = 4e5+10;
const int MOD = 1e9+7;

vector<int> ch[N];
int fa[N], top[N], sz[N], son[N], dep[N], dfn[N], cnt;

void dfs1(int p) {
    sz[p] = 1; dep[p] = dep[fa[p]] + 1;
    for(auto q: ch[p]) {
        dfs1(q);
        sz[p]+=sz[q];
        if(sz[q]>sz[son[p]]) {
            son[p] = q;
        }
    }
}

void dfs2(int p) {
    dfn[p] = ++cnt;
    if(p==son[fa[p]]) top[p] = top[fa[p]];
    else top[p] = p;
    if(son[p]) dfs2(son[p]);
    for(auto q: ch[p]) if(q!=son[p]) {
        dfs2(q);
    }
}

ULL sm[N], a[N], b[N];
ULL len[N];

void up(int p) {
    sm[p] = sm[lc(p)]+sm[rc(p)];
}

void tag(int p, ULL A, ULL B) {
    dbg("apply", p, A, B);
    a[p]*=A; b[p] = A*b[p]+B;
    sm[p] = sm[p]*A+B*len[p];
}

void down(int p) {
    if(a[p]==1 && b[p]==0) return;
    tag(lc(p), a[p], b[p]);
    tag(rc(p), a[p], b[p]);
    a[p] = 1; b[p] = 0;
}

void build(int p, int l, int r) {
    a[p] = 1;
    sm[p] = b[p] = 0;
    len[p] = r-l+1;
    if(l==r) {
        return;
    }
    int mid = l+r>>1;
    build(lc(p), l, mid);
    build(rc(p), mid+1, r);
    up(p);
}

ULL AA, BB;

void tag(int p, int l, int r, int ql, int qr) {
    if(ql<=l && r<=qr) {
        tag(p, AA, BB);
        return;
    }
    down(p);
    int mid = l+r>>1;
    if(ql<=mid) tag(lc(p), l, mid, ql, qr);
    if(qr>mid) tag(rc(p), mid+1, r, ql, qr);
    up(p);
}

ULL query(int p, int l, int r, int ql, int qr) {
    if(ql<=l && r<=qr) {
        dbg(p, l, r, sm[p]);
        return sm[p];
    }
    down(p);
    int mid = l+r>>1;
    ULL ans = 0;
    if(ql<=mid) ans+=query(lc(p), l, mid, ql, qr);
    if(qr>mid) ans+=query(rc(p), mid+1, r, ql, qr);
    return ans;
}

template<typename T>
void go(int u, int v, T&& f) {
    int uu = top[u], vv = top[v];
    while(uu!=vv) {
        if(dep[uu] < dep[vv]) { swap(uu, vv); swap(u, v); }
        f(dfn[uu], dfn[u]);
        u = fa[uu]; uu = top[u];
    }
    if(dep[u]<dep[v]) swap(u, v);
    f(dfn[v], dfn[u]);
}

int main() {
    int n, m;
    while (~scanf("%d", &n)) {
        fill(son, son+n+1, 0);
        FOR (i, 1, n + 1) ch[i].clear();
        FOR(i, 1, n) {
            int x; scanf("%d", &x);
            fa[i+1] = x;
            ch[x].push_back(i+1);
        }
        cnt = 0;
        son[0] = -1;
        dfs1(1);
        dfs2(1);
        build(1, 1, n);
        FOR(i, 1, n+1) dbg(i, dfn[i]);
        scanf("%d", &m);
        while(m--) {
            int op, u, v; scanf("%d", &op);
            ULL x;
            if(op==2) {
                scanf("%d%d%llu", &u, &v, &x);
                AA = 1; BB = x;
                go(u, v, [&](int l, int r) { tag(1, 1, n, l, r); dbg(l, r); });
            } else if(op==1) {
                scanf("%d%d%llu", &u, &v, &x);
                AA = x; BB = 0;
                go(u, v, [&](int l, int r) { tag(1, 1, n, l, r); dbg(l, r); });
            } else if(op==3) {
                scanf("%d%d", &u, &v);
                AA = ~0ULL; BB = ~0ULL;
                go(u, v, [&](int l, int r) { tag(1, 1, n, l, r); dbg(l, r); });
            } else if(op==4) {
                scanf("%d%d", &u, &v);
                ULL ans = 0;
                go(u, v, [&](int l, int r) {
                    ULL ret = query(1, 1, n, l, r);
                    dbg(l, r, ret);
                    ans+=ret;
                });
                printf("%llu\n", ans);
            }
        }
    }
    return 0;
}
