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
/////////////////////////////////////////// 

typedef pair<int, int> P;

#define lc(x) (((x)<<1))
#define rc(x) (((x)<<1)|1)

const int N = 1e5+10;
const int M = 1e4+100;
const int NX = N*4;

P val[NX];

int rb[N], Q[N], n, m, q;
P a[N], ans[N];

void build(int p, int l, int r) {
	if(l==r) {
		val[p] = P(a[l].second, l);
		return;
	}
	int mid = l+r>>1;
	build(lc(p), l, mid);
	build(rc(p), mid+1, r);
	val[p] = min(val[lc(p)], val[rc(p)]);
}

P query(int p, int l, int r, int rb) {
	if(rb>=r) return val[p];
	int mid = l+r>>1;
	if(rb>mid) return min(query(lc(p), l, mid, rb), query(rc(p), mid+1, r, rb));
	return query(lc(p), l, mid, rb);
}

void change(int p, int l, int r, int pos) {
	dbg(p, l, r, pos);
	if(l==r) {
		val[p] = P(N, 0);
		return;
	}
	int mid = l+r>>1;
	if(pos<=mid) change(lc(p), l, mid, pos);
	else change(rc(p), mid+1, r, pos);
	val[p] = min(val[lc(p)], val[rc(p)]);
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i<n; ++i) {
		scanf("%d", &a[i].first); a[i].second = i;
	}
	scanf("%d", &q);
	for(int i = 0; i<q; ++i) scanf("%d", Q+i);
	sort(a, a+n);
	for(int i = 1; i<=M; ++i) rb[i] = upper_bound(a, a+n, P(i, n))-a;
	int rem = 0, last = n, cur = 0;
	build(1, 0, n-1);
	{
		for(int i = 1; i<N; ++i) {
			//dbg("day", i);
			rem+=m;
			while(last>0 && rem>0 && rb[rem]>0) {
				//dbg("round");
				auto ret = query(1, 0, n-1, rb[rem]-1);
				//dbg(ret.first, ret.second, a[ret.second].first, a[ret.second].second);
				if(ret.first==N) break;
				rem-=a[ret.second].first; ++cur; --last;
				change(1, 0, n-1, ret.second);
			}
			ans[i].first = cur;
			ans[i].second = rem;
			//dbg(cur, rem);
		}
		
	}
	for(int i = 0; i<q; ++i) printf("%d %d\n", ans[Q[i]].first, ans[Q[i]].second);
	return 0;
}
