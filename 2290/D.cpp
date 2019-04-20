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

typedef pair<int, int> P;

int aa[10] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int NOW, NXT;

LL dp[2][5000];

LL mx[2][100], mi[2][100];

const int LIM = 2500;
const int LIM2 = 50;
const int LIX = 46;
const LL INF = 1e15;

int nums[10];

void Apply(LL *val) {
    // FOR(i, -10, 10) dbg(i, val[i]);
    FOR(delta, -LIX, 0) {
        FORD(i, 5000-1, -delta-1) {
            dp[NXT][i] = max(dp[NXT][i], dp[NOW][i+delta]+val[delta]);
            // if(i>2498 && i<2502) dbg(NXT, i, dp[NXT][i]);
        }
    }
    FOR(delta, 0, LIX+1) {
        FOR(i, 0, 5000-delta) {
            dp[NXT][i] = max(dp[NXT][i], dp[NOW][i+delta]+val[delta]);
            // if(i>2498 && i<2502) dbg(NXT, i, dp[NXT][i]);
        }
    }
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int n; scanf("%d", &n);
        fill(dp[0], dp[0]+5000, -INF);
        dp[0][LIM] = 0;
        NOW = 0;
        FOR(i, 0, (n+1)/2) {
            NXT = NOW^1;
            fill(dp[NXT], dp[NXT]+5000, -INF);
            char op = '+';
            if(i != 0) scanf("%c", &op);
            fill(mx[0], mx[0]+100, -INF);
            fill(mi[0], mi[0]+100, INF);
            mx[0][LIM2] = mi[0][LIM2] = 0;
            int num = 0, now = 0, c = 0;
            scanf("%d", &num); dbg(num);
            LL q = 1;
            do {
                nums[c++] = num % 10;
                num /= 10; q*=10;
            } while(num);
            q /= 10;
            FORD(i, c-1, -1) {
                int nxt = now^1;
                fill(mx[nxt], mx[nxt]+100, -INF);
                fill(mi[nxt], mi[nxt]+100, INF);
                int x = nums[i];
                FOR(i, c>1 && (i == c-1), 10) {
                    int delta = abs(aa[i]-aa[x]);
                    if(aa[i] == aa[x]) FOR(j, 0, 100) mx[nxt][j] = mx[now][j] + i*q;
                    else if(aa[i] > aa[x]) FORD(j, 99, delta-1) mx[nxt][j] = max(mx[nxt][j], mx[now][j-delta] + i*q);
                    else FOR(j, 0, 100-delta) mx[nxt][j] = max(mx[nxt][j], mx[now][j+delta] + i*q);
                    if(aa[i] == aa[x]) FOR(j, 0, 100) mi[nxt][j] = mi[now][j] + i*q;
                    else if(aa[i] > aa[x]) FORD(j, 99, delta-1) mi[nxt][j] = min(mi[nxt][j], mi[now][j-delta] + i*q);
                    else FOR(j, 0, 100-delta) mi[nxt][j] = min(mi[nxt][j], mi[now][j+delta] + i*q);
                }
                q /= 10;
                now = nxt;
            }
            // if(T == 1) FOR(i, 0, 100) dbg(i-LIM2, mx[now][i], mi[now][i]);
            if(i == 0) {
                Apply(mx[now]+LIM2);
            } else if(op == '+') {
                FOR(i, 0, 99) mx[now][i] = max(mx[now][i], -mi[now][i+1]);
                Apply(mx[now]+LIM2);
            } else {
                FOR(i, 0, 99) mx[now][i] = max(mx[now][i], -mi[now][i+1]);
                Apply(mx[now]+LIM2-1);
            }
            NOW = NXT;
            // FOR(i, -10, 10) dbg(NOW, i+LIM, dp[NOW][i+LIM]);
        }
        printf("%lld\n", dp[NOW][LIM]);
    }
    return 0;
}