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

const int N = 1e5+10;

struct bit {
	
	int a[N];
	
	void add(int p, int v) {
		while(p<N) {
			if(a[p]<v) a[p] = v;
			p+=p&-p;
		}
	}
	
	int sum(int p) {
		int val = a[p];
		while(p) {
			val = max(val, a[p]);
			p&=p-1;
		}
		return val;
	}
} A, B;

int n, m = 0;
LL ans = 0;

int x[N], y[N], z[N];

int ID(int x) {
	return lower_bound(z, z+m, x)-z;
}

int main() {
	scanf("%d", &n);
	FOR(i, 0, n) {
		scanf("%d%d", x+i, y+i);
		z[m++] = x[i]; z[m++] = y[i];
	}
	sort(z, z+m); m = unique(z, z+m)-z;
	FORD(i, n-1, -1) {
		int h = A.sum(m-ID(x[i]));
		int w = B.sum(m-ID(y[i]));
		if(h>y[i] || w>x[i]) continue;
		ans+=y[i]-h+x[i]-w;
		dbg(h, w, ans);
		A.add(m-ID(x[i]), y[i]);
		B.add(m-ID(y[i]), x[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
