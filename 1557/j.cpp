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

const int N = 510;
const int M = N*N;
const int K = 20;

typedef pair<int, int> P;
typedef pair<int, P> PP;

PP e[M*2];

int fa[M];

vector<int> E[M];

int Fa(int x) {
	return fa[x]==x?x:(fa[x] = Fa(fa[x]));
}

int pr[M][K], dep[M];

void dfs(int p, int _f) {
	pr[p][0] = _f;
	FOR(k, 1, K) pr[p][k] = pr[pr[p][k-1]][k-1];
	for(auto q: E[p]) {
		if(q==_f) continue;
		dep[q] = dep[p]+1;
		dfs(q, p);
	}
}

int lca(int x, int y) {
	if(dep[x]<dep[y]) {
		swap(x, y);
	}
	int d = dep[x]-dep[y];
	FORD(k, K-1, -1) if(d>>k) {
		d -= (1<<k);
		x = pr[x][k];
	}
	if(x==y) return x;
	FORD(k, K-1, -1) if(pr[x][k]!=pr[y][k]) {
		x = pr[x][k];
		y = pr[y][k];
	}
	return pr[x][0];
}

int main() {
	int n, m, k = 0;
	scanf("%d%d", &n, &m);
	iota(fa, fa+M, 0);
	FOR(i, 1, n+1)
		FOR(j, 1, m+1) {
			int a, b;
			char s[5];
			scanf("%s%d%s%d", s, &a, s, &b);
			if(i<n) {
				e[k++] = PP(a, P(i*m+j, (i+1)*m+j));
			}
			if(j<m) {
				e[k++] = PP(b, P(i*m+j, i*m+(j+1)));
			}
		}
	sort(e, e+k, greater<PP>());
	FOR(i, 0, k) {
		auto p = e[i].second;
		int u = p.first, v = p.second;
		int fu = Fa(u), fv = Fa(v);
		if(fu!=fv) {
			E[u].push_back(v);
			E[v].push_back(u);
			fa[fu] = fv;
			dbg(u, v);
		}
	}
	dfs(1*m+1, 0);
	int Q; scanf("%d", &Q);
	while(Q--) {
		int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		int p = x1*m+y1, q = x2*m+y2;
		int f = lca(p, q);
		dbg(p, q, f);
		dbg(dep[p], dep[q], dep[f]);
		printf("%d\n", dep[p]+dep[q]-dep[f]*2);
	}
	return 0;
}
