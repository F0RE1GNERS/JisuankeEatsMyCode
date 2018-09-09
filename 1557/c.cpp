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

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;

const int N = 5E5 + 100;
string digits[N];
int scnt, b[N][8];

int raw_data[] = {6, 10000, 7, 36, 8, 720, 9, 360, 10, 80, 11, 252, 12, 108, 13, 72, 14, 54, 15, 180, 16, 72, 17, 180, 18, 119, 19, 36, 20, 360, 21, 1080, 22, 144, 23, 1800, 24, 3600};
int SCORES[30];
int MAGIC[8][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6},
};

int score(const string &s, int idx) {
    FOR (i, 0, 8) {
        int sc = 0;
        FOR (j, 0, 3) sc += s[MAGIC[i][j]] - '0';
        b[idx][i] = SCORES[sc];
    }
}

void generate() {
    string s = "123456789";
    do {
        digits[scnt] = s;
        score(s, scnt);
        scnt++;
    } while (next_permutation(s.begin(), s.end()));
}

int prepare_raw_data() {
    FOR (i, 0, 19)
        SCORES[raw_data[2 * i]] = raw_data[2 * i + 1];
}

LL f[N][8]; int d[N];

int main() {
    prepare_raw_data();
    generate();
    assert (scnt == 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1);
    int T; cin >> T;
    while (T--) {
        string raw_s;
        FOR (i, 0, 3) { string t; cin >> t; raw_s += t; }
        gp_hash_table<int, int> repo;
        FOR (idx, 0, scnt) {
            auto s = raw_s; auto t = digits[idx];
            bool ok = true;
            int id = 0;
            FOR (i, 0, 9) {
                if (isdigit(s[i]) && s[i] != t[i]) { ok = false; break; }
                if (s[i] == '*') s[i] = t[i];
                else if (s[i] == '#') s[i] = '0';
                id = id * 10 + s[i] - '0';
            }
            if (!ok) continue;
            int kk = -1;
            if (repo.find(id) == repo.end()) {
                repo[id] = kk = idx;
                fill(f[kk], f[kk] + 8, 0);
                d[kk] = 0;
            } else kk = repo[id];

            d[kk]++;
            FOR (i, 0, 8) f[kk][i] += b[idx][i];
        }

        double ans = 0;

        for (auto& x: repo) {
            int kk = x.second;
            // FOR (i, 0, 8) dbg(kk, i, f[kk][i]);
            double r = 1.0 * (*max_element(f[kk], f[kk] + 8)) / d[kk];
            // dbg(r);
            ans += r;
        }

        printf("%.8f\n", ans / (repo.size()));
    }
}
