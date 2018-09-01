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

const int M = 4096+10;
const int MOD = 1e9+7;
const int MOD2 = MOD-1;

int a[M], b[5], k;

int fp[M];

int x[M];

int f(int x) {
	int ans = 0;
	for(int i = 0; i<5; ++i) ans = (ans*x+b[i])%k;
	return ans==0?k:ans;
}

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}

int main() {
	memset(fp, -1, sizeof(fp));
	int x1;
	LL nx = 0, nt = 0; bool ub = false;
	{
		static char ch = getchar();
		for(; '0'<=ch && ch<='9'; ch = getchar()) {
			nx = (nx*10+ch-'0')%MOD2;
			nt = (nt*10+ch-'0');
			if(nt>M) ub = true;
		}
	}
	scanf("%d", a); dbg(a[0]);
	for(int i = 0; i<5; ++i) scanf("%d", b+i);
	scanf("%d", &k);
	fp[a[0]] = 0;
	int n = 0, cnt = 0;
	while(++n<nt || ub){
		a[n] = f(a[n-1]);// dbg(n, a[n-1], a[n]);
		if(fp[a[n]]>-1) break;
		fp[a[n]] = n;
	}
	dbg(n);
	int t, r;
	for(t = 11, r = 0; t>=0 && r<n; --t) {
		int p = -1;
		for(int i = r; i<n; ++i) if((a[i]>>t)>0) {
			p = i;
			break;
		}
		if(p==-1) continue;
		dbg(t, r, p);
		if(p!=r) swap(a[p], a[r]);
		for(int i = r+1; i<n; ++i) if((a[i]>>t)>0) a[i]^=a[r];
		++r;
	}
	dbg(r);
	dbg(nx);
	LL ans1 = bin(2, nx, MOD);
	dbg(ans1);
	nx-=r; if(nx<0) nx+=MOD2;
	dbg(nx);
	LL ans2 = bin(2, nx, MOD);
	dbg(ans2);
	LL ans = ans1-ans2;
	if(ans<0) ans+=MOD;
	printf("%lld\n", ans);
	return 0;
}
