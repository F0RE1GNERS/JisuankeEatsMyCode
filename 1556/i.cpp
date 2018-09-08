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
typedef double ld;

const int N = 6e4+10;
const int M = 1e6+10;

int mp[N];

char s[M];

int d[M], d2[M];

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		memset(mp, 0, sizeof(mp));
		int n, m, nx; scanf("%d%d", &m, &n);
		FOR(i, 0, n) {
			int x, y = 0;
			scanf("%d%s", &x, s);
			FOR(j, 0, strlen(s)) y = y*3+s[j]-'0'+1;
			dbg(y, x);
			mp[y] = x;
		}
		scanf("%s", s);
		n = 0;
		FOR(i, 0, strlen(s)) {
			int x = s[i]<='9'?(s[i]-'0'):(s[i]>='a'?(s[i]-'a'+10):(s[i]-'A'+10));
			d[n] = (x>>3)&1;
			d[n+1] = (x>>2)&1;
			d[n+2] = (x>>1)&1;
			d[n+3] = (x>>0)&1;
			n+=4;
		}
		nx = 0;
		for(int i = 0; i+9<=n; i+=9) {
			int x = 0;
			for(int j = 0; j<9; ++j) {
				x^=d[i+j];
			}
			if(x!=1) continue;
			for(int j = 0; j<8; ++j) d2[nx++] = d[i+j];
		}
		dbg(nx);
		int now = 0;
		for(int i = 0; i<nx && m>0; ++i) {
			now = now*3+d2[i]+1;
			//dbg(now, mp[now]);
			if(mp[now]!=0) {
				putchar(mp[now]); now = 0; --m;
			}
		}
		putchar('\n');
	}
}
