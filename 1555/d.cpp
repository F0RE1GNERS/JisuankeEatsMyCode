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

typedef double ld;
const ld INF = 1e100;
const ld EPS = 1e-12;
const ld PI = acos(-1.0);

// -1: less than 0
// 1: greater than 0
inline int dcmp(ld x) {
    return fabs(x) < EPS ? 0 : (x > 0 ? 1 : -1);
}

struct PT {
    ld x, y;
    PT() { x = 0; y = 0; }
    PT(ld x, ld y): x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator + (const PT &p) const { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p) const { return PT(x - p.x, y - p.y); }
    PT operator * (ld c) const { return PT(x * c, y * c); }
    PT operator / (ld c) const { return PT(x / c, y / c); }
    inline int operator < (const PT& p) const {
        return dcmp(x - p.x) < 0 || (dcmp(x - p.x) == 0 && dcmp(y - p.y) < 0);
    }
    inline bool operator == (const PT& p) const { return dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0; }
    inline bool operator != (const PT& p) const { return !((*this) == p); }
};

ld dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
ld dist2(PT p, PT q) { return dot(p - q, p - q); }
inline ld cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }
ostream &operator << (ostream &os, const PT &p) {
    return (os << "(" << p.x << "," << p.y << ")");
}
istream &operator >> (istream &is, PT &p) {
    return (is >> p.x >> p.y);
}

struct Line {
    PT p, v;
    double ang;

    Line() {}
    Line(PT from, PT to) : p(from), v(to - from) { ang = atan2(v.y, v.x); }
    friend bool operator<(Line a, Line b) {
        return a.ang < b.ang;
    }
};

bool OnLeft(Line L, PT p) {
    return dcmp(cross(L.v, p - L.p)) >= 0;
}

PT GetIntersection(Line a, Line b) {
    PT u = a.p - b.p;
    ld t = cross(b.v, u) / cross(a.v, b.v);
    return a.p + a.v * t;
}

vector<PT> HalfplaneIntersection(vector<Line>& L) {
    int n = L.size();
    sort(L.begin(), L.end());

    int first, last;
    vector<PT> p(n);
    vector<Line> q(n);
    q[first = last = 0] = L[0];
    for (int i = 1; i < n; i++) {
        while (first < last && !OnLeft(L[i], p[last - 1])) last--;
        while (first < last && !OnLeft(L[i], p[first])) first++;
        q[++last] = L[i];
        if (dcmp(cross(q[last].v, q[last - 1].v)) == 0) {
            last--;
            if (OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if (first < last) p[last - 1] = GetIntersection(q[last - 1], q[last]);
    }
    while (first < last && !OnLeft(q[first], p[last - 1])) last--;
    if (last - first <= 1) return vector<PT>();
    p[last] = GetIntersection(q[last], q[first]);

    return vector<PT>(p.begin() + first, p.begin() + last + 1);
}

PT RotateCCW90(PT p) { return PT(-p.y, p.x); }

vector<PT> new_polygon(vector<PT> P, double offset) {
    vector<Line> L; int n = P.size(); P.push_back(P[0]);
	FOR (i, 0, n) {
		PT way = RotateCCW90(P[i+1]-P[i]);
		way = way*(offset/sqrt(dot(way, way)));
		L.emplace_back(P[i]+way, P[i+1]+way);
	}
    FOR (i, 0, L.size()) dbg(L[i].p, L[i].v);
	return HalfplaneIntersection(L);
}

inline ld Area(PT a, PT b, PT c) { return fabs(cross(c - a, b - a)); }

int n, r;
vector<PT> poly;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n >> r;
        poly.resize(n);
        FOR (i, 0, n) cin >> poly[i];
        reverse(poly.begin(), poly.end());
        poly = new_polygon(poly, r);
        FOR (i, 0, poly.size()) dbg(poly[i]);
        // assert ((int) poly.size() == n);

        // ld area = 0;
        // FOR (i, 0, poly.size()) FOR (j, i + 1, poly.size()) FOR (k, j + 1, poly.size()) {
        //     area = max(area, Area(poly[i], poly[j], poly[k]));
        // }
        // dbg(area);
        area = 0;
        n = poly.size();
        FOR (i, 0, n) FOR (j, i + 1, n) {
            int l = j + 1, r = n - 1;
            while (l < r) {
                int mid1 = max((2 * l + r) / 3, l);
                int mid2 = min((l + 2 * r) / 3, r);
                assert (mid1 >= l && mid2 <= r);
                if (Area(poly[i], poly[j], poly[mid1]) < Area(poly[i], poly[j], poly[mid2])) {
                    if (mid1 == l) break;
                    l = mid1;
                }
                else {
                    if (mid2 == r) break;
                    r = mid2;
                }
            }
            dbg(i, j, l, r);
            FOR (k, j + 1, n) area = max(area, Area(poly[i], poly[j], poly[k]));
        }
        printf("%.9f\n", area);
    }

}
