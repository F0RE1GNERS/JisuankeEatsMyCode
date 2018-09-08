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

const int N = 800;

typedef double ld;

const ld INF = 1e100;
const ld EPS = 1e-9;
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

PT RotateCCW90(PT p) { return PT(-p.y, p.x); }
PT RotateCW90(PT p) { return PT(p.y, -p.x); }
PT RotateCCW(PT p, ld t) {
    return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}

ld dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
ld dist2(PT p, PT q) { return dot(p - q, p - q); }
ld cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }
ostream &operator << (ostream &os, const PT &p) {
    return (os << "(" << p.x << "," << p.y << ")");
}
istream &operator >> (istream &is, PT &p) {
    return (is >> p.x >> p.y);
}

int n, S;
double R;
PT a[N];

struct P {
	PT first;
	int second;
	ld ang;
	P(PT x, int y) {
		first = x; second = y; ang = atan2(x.y, x.x);
	}
	P() {
		first = PT(0, 0); second = 0, ang = 0;
	}
};

P b[N];

bool flag[N];

bool cmp(P& p, P& q) {
	return (p.first==q.first?p.second>q.second:p.ang<q.ang);
}

int check(double r) {
    int res = 0;
    FOR (i, 0, n) {
    	dbg(r, i);
		memset(flag, 0, sizeof(flag));
	    int cur = 0, m = 0;
		FOR (j, 0, n) if(a[i]!=a[j]) {
	        PT cent = (a[i] + a[j]) / 2;
	        PT delta = (a[j] - a[i]) / 2;
	        PT rt = RotateCCW90(cent - a[i]);
	        ld p = r * r - dist2(cent, a[i]);
	        if(p<0) continue;
	        rt = rt * sqrt(p / dot(rt, rt));
	        //dbg(delta, rt);
	        b[m++] = P(delta+rt, -j-1);
	        b[m++] = P(delta-rt, j+1);
	    } else {
	    	++cur;
		}
	    sort(b, b+m, cmp);
	    for(int j = 0; j<m; ++j) if(b[j].second>0) {
	    	if(flag[b[j].second]) ++cur;
		} else {
			flag[-b[j].second] = true;
		}
		for(int j = 0; j<m; ++j) {
			cur+=b[j].second>0?1:-1;
			dbg(b[j].first, b[j].second, cur);
			res = max(res, cur);
		}
	}
    return res;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> S;
        FOR (i, 0, n) cin >> a[i];
        cin >> R;
        if (n < S) {
            puts("The cake is a lie.");
            continue;
        }
        if (S == 1) {
            printf("%.4f\n", R);
            continue;
        }
        // check(5);
        double l = 0, r = 20000;
        while (r - l > EPS) {
            double mid = (l + r) / 2;
            if (check(mid) >= S)
                r = mid;
            else l = mid;
            //break;
        }
        printf("%.4f\n", l + R);
    }
}
