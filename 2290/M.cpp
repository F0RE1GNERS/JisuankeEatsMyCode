#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
#else
#define dbg(...)
#endif // zerol
void err() { cout << "\033[39;0m" << endl; }
template<typename T, typename... A>
void err(T a, A... x) { cout << a << ' '; err(x...); }
// ----------------------------------------------------------------------------------------

const int N = 1e5+10;

char s[N], t[N];
int nxt[N][30];

int main() {
    scanf("%s", s+1);
    int n = strlen(s+1);
    s[n+1] = 'z' + 1;
    FOR(i, 0, 30) nxt[n+1][i] = n+1;
    FORD(i, n, -1) {
        FOR(j, 0, 30) nxt[i][j] = nxt[i+1][j];
        nxt[i][s[i+1]-'a'] = i+1;
    }
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%s", t);
        int p = 0, m = strlen(t);
        FOR(i, 0, m) p = nxt[p][t[i]-'a'];
        dbg(p);
        puts(p<=n?"YES":"NO");
    }
    return 0;
}