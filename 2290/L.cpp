#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(x...) do { cout << "Debug: " << #x << " -> "; err(x); } while (0)
void err() { cout << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cout << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cout << a << ' '; err(x...); }
#else
#define dbg(...)
#endif
// -----------------------------------------------------------------------------

#define y1 yy1
#define nxt(i) ((i + 1) % s.size())
typedef long double LD;
const LD PI = 3.14159265358979323846;
const LD eps = 1E-10;
int sgn(LD x) { return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1); }
struct L;
struct P;
typedef P V;
struct P {
    LD x, y;
    explicit P(LD x = 0, LD y = 0): x(x), y(y) {}
    explicit P(const L& l);
};
struct L {
    P s, t;
    L() {}
    L(P s, P t): s(s), t(t) {}
};

P operator + (const P& a, const P& b) { return P(a.x + b.x, a.y + b.y); }
P operator - (const P& a, const P& b) { return P(a.x - b.x, a.y - b.y); }
P operator * (const P& a, LD k) { return P(a.x * k, a.y * k); }
P operator / (const P& a, LD k) { return P(a.x / k, a.y / k); }
inline bool operator < (const P& a, const P& b) {
    return sgn(a.x - b.x) < 0 || (sgn(a.x - b.x) == 0 && sgn(a.y - b.y) < 0);
}
bool operator == (const P& a, const P& b) { return !sgn(a.x - b.x) && !sgn(a.y - b.y); }
P::P(const L& l) { *this = l.t - l.s; }
ostream &operator << (ostream &os, const P &p) {
    return (os << "(" << p.x << "," << p.y << ")");
}
istream &operator >> (istream &is, P &p) {
    return (is >> p.x >> p.y);
}

LD dist(const P& p) { return sqrt(p.x * p.x + p.y * p.y); }
LD dot(const V& a, const V& b) { return a.x * b.x + a.y * b.y; }
LD det(const V& a, const V& b) { return a.x * b.y - a.y * b.x; }
LD cross(const P& s, const P& t, const P& o = P()) { return det(s - o, t - o); }
// --------------------------------------------

P rotation(const P& p, const LD& r) { return P(p.x * cos(r) - p.y * sin(r), p.x * sin(r) + p.y * cos(r)); }
P RotateCCW90(const P& p) { return P(-p.y, p.x); }
P RotateCW90(const P& p) { return P(p.y, -p.x); }
P l_intersection(const L& a, const L& b) {
    LD s1 = det(P(a), b.s - a.s), s2 = det(P(a), b.t - a.s);
    return (b.s * s2 - b.t * s1) / (s2 - s1);
}
bool parallel(const L& a, const L& b) {
    return !sgn(det(P(a), P(b)));
}
bool l_eq(const L& a, const L& b) {
    return parallel(a, b) && parallel(L(a.s, b.t), L(b.s, a.t));
}

int n;
LD K, X, Y;
LD ans = 0;
L official_line;
int p_with_line(const P& p, const L& seg) {
    P a = seg.s, b = seg.t;
    return sgn(det(p - a, p - b));
}

void dfs(int dep, const L& branch, LD dd) {
    if (dep == n) return;
    V vec = V(branch);
    int p1 = p_with_line(branch.s, official_line);
    int p2 = p_with_line(branch.t, official_line);
    dbg(branch.s, branch.t, p1, p2);
    if (p1 != p2) {
        ans += dist(l_intersection(branch, official_line) - branch.s);
        return;
    } else if (p1 == 0 && p2 == 0) {
        ans += dist(P(branch));
        return;
    } else assert (!l_eq(branch, official_line));
    ans += dd;
    dfs(dep + 1, {branch.t, branch.t + rotation(P(branch), PI / 3) / 4}, dd / 4);
    dfs(dep + 1, {branch.t, branch.t + P(branch) / 4}, dd / 4);
    dfs(dep + 1, {branch.t, branch.t + rotation(P(branch), -PI / 3) / 4}, dd / 4);
}

int main() {
    int t; cin >> t;
    while (t--) {
        LD x, y, k, l;
        cin >> l >> n >> x >> y >> k;
        official_line = L(P(x, y), P(x + 100, y + k * 100));
        ans = 0;
        dbg(l);
        dfs(0, {P(0, 0), P(0, l)}, l);
        printf("%.6f\n", (double) ans);
    }
}