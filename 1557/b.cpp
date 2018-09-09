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

const int N = 1E3+10;
const int M = 200+10;
const int TH = 100;

int a[N], b[N], c[N];
int n, m, k, l;

// 4: Good
// 2: Normal
// 1: Bad

int dp[N][M];

int dfs(int p, int now) {
	dbg(p, now);
	if(p==n) {
		return now>=k?4:(now<=l?1:2);
	}
	if(dp[p][now+TH]) return dp[p][now+TH];
	int &ans = dp[p][now+TH];
	int want, hate;
	if(p&1) {
		want = 1, hate = 4;
	} else {
		want = 4, hate = 1;
	}
	bool flag = false;
	if(a[p]) {
		int ret= dfs(p+1, min(now+a[p], TH));
		if(ret==want) return ans = want;
		if(ret!=hate) flag = true;
	}
	if(b[p]) {
		int ret = dfs(p+1, max(now-b[p], -TH));
		if(ret==want) return ans = want;
		if(ret!=hate) flag = true;
	}
	if(c[p]) {
		int ret= dfs(p+1, -now);
		if(ret==want) return ans = want;
		if(ret!=hate) flag = true;
	}
	if(flag) return ans = 2;
	else return ans = hate;
}

int main() {
	scanf("%d%d%d%d", &n, &m, &k, &l);
	FOR(i, 0, n) scanf("%d%d%d", a+i, b+i, c+i);
	int ret = dfs(0, m);
	puts(ret==4?"Good Ending":(ret==2?"Normal Ending":"Bad Ending"));
	return 0;
}
