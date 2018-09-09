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

const int N = 1e6+10;

char s[N];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n, ans; char c; scanf("%d %c", &n, &c); ans = n;
		scanf("%s", s); ans = n*2;
		int i = 0;
		while(i<n && s[i]==c) {
			++i; ans-=2;
		}
		if(i<n && abs(s[i]-c)<10) --ans;
		printf("%d\n", max(ans, 1));
	}
	return 0;
}
