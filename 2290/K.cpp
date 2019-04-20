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

int a[N], a4[N];

int range4(int l, int r) {
    return a4[r]^(l<4?0:a4[l-4]);
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        FOR(i, 1, n+1) scanf("%d", a+i);
        FOR(i, 0, 4) a4[i] = a[i]; FOR(i, 4, n+1) a4[i] = a[i]^a4[i-4];
        int t; scanf("%d", &t);
        while(t--) {
            int l, r; scanf("%d%d", &l, &r); int len = r-l+1;
            switch(len%4) {
                case 0:
                    puts("0");
                    break;
                case 1:
                    printf("%d\n", range4(l, r));
                    break;
                case 2:
                    printf("%d\n", range4(l, r-1)^range4(l+1, r));
                    break;
                case 3:
                    printf("%d\n", range4(l+1, r-1));
                    break;
            }
        }
        
    }
    return 0;
}