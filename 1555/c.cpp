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
// -----------------------------------------------------------------------------

const int score[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 1, 2};
const int idx[] = {0, 11, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

struct Hand {
    Hand() { memset(cnt, 0, sizeof cnt); tot = 0; }
    int cnt[13], tot;

    int first() {
        FOR (i, 0, 13) if (cnt[i]) return i;
        assert (0);
    }
    void clear() { memset(cnt, 0, sizeof cnt); tot = 0; }
    inline void insert(int x) { cnt[x]++; tot++; }
    inline int size() { return tot; }
    inline void erase(int x) { assert (cnt[x]); cnt[x]--; tot--; }
    inline bool empty() { return tot == 0; }
    inline bool any() { return tot != 0; }
    inline int count(int x) { return cnt[x]; }
    int penalty() {
        int res = 0;
        int t = accumulate(cnt, cnt + 13, 0);
        assert (t == tot);
        FOR (i, 0, 13) res += cnt[i] * score[i];
        return res;
    }
};

const int N = 500;
int n, m;
deque<int> pile;
Hand hand[N];
int last_player, last_card;

void draw(int player) {
    if (!pile.empty()) {
        int y = pile.front(); pile.pop_front();
        dbg("draw", player, y);
        hand[player].insert(y);
    } else {
        dbg("draw", "nothing");
    }
}

void play(int player) {
    int now = -1;
    if (last_card < 0) {
        if (!hand[player].empty()) now = hand[player].first();
    } else if (last_card < 12) {
        if (hand[player].count(last_card + 1)) now = last_card + 1;
        else if (hand[player].count(12)) now = 12;
    }
    dbg("play", player, now);
    if (now >= 0) {
        hand[player].erase(now);
        last_player = player; last_card = now;
        if (hand[player].empty()) throw player;
    }
}

void turn(int player) {
    if (last_player == player) {
        FOR (i, 0, n)
            draw((player + i) % n);
        last_card = -1;
    }
    play(player);
}

int main() {
    int T, cas = 0; cin >> T;
    while (T--) {
        cin >> n >> m;
        pile.clear();
        FOR (i, 0, n) hand[i].clear();
        last_player = -1; last_card = -1;
        FOR (i, 0, m) {
            int x; scanf("%d", &x);
            pile.push_back(idx[x]);
        }
        // assert (m >= 5 * n);
        printf("Case #%d:\n", ++cas);
        FOR (i, 0, n) {
            FOR (j, 0, 5)
                draw(i);
        }
        try {
            while (true) {
                FOR (i, 0, n) turn(i);
            }
        } catch (int winner) {
            FOR (i, 0, n) {
                if (i != winner) printf("%d\n", hand[i].penalty());
                else puts("Winner");
            }
        }
    }
}
