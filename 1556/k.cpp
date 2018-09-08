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

const int N = 1E2+10;

int table[20] = {1, 2, 3, 5, 7, 11, 13, 17, 23, 31, 37, 53, 71, 73, 113, 131, 137, 173, 311, 317 };

int cnt = 20;

char s[N];

int main() {
	int T, n, m; scanf("%d", &T);
	FOR(cas, 1, T+1) {
		scanf("%s", s); printf("Case #%d: ", cas);
		if((n = strlen(s))>5) {
			printf("%d\n", table[cnt-1]);
		} else {
			int m = 0;
			FOR(i, 0, n) m = m*10+s[i]-'0';
			printf("%d\n", *(upper_bound(table, table+cnt, m)-1));
		}
	}
	return 0;
}
/*

const int N = 1E2+10;

int pr[5] = {1, 2, 3, 5, 7};
int mask[5] = {
	21, 4, 17, 4, 5
};

typedef pair<pair<int, int>, LL> P;

P q[N];

int main() {
	int head = 0, tail = 0;
	q[tail++] = P(make_pair(31, 0), 0);
	while(head<tail && tail<N) {
		auto x = q[head++];
		dbg(x.first.first, x.first.second, x.second);
		
		for(int i = 0; i<5; ++i) if((x.first.first>>i)&1) {
			int sum = x.first.second+pr[i];
			if(sum%3==0 && x.second!=0) continue;
			q[tail] = P(make_pair(x.first.first&mask[i], sum), x.second*10+pr[i]);
			dbg(q[tail].second);
			tail++;
		}
	}
}
*/
