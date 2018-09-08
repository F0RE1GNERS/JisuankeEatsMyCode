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

const int N = 200;
int n;
char s[N];

struct P {
    LL min, max;
};

P operator + (const P& x, const P& y) {
    return {x.min + y.min, x.max + y.max};
}
P operator - (const P& x, const P& y) {
    return {x.min - y.max, x.max - y.min};
}
P operator * (const P& x, const P& y) {
    vector<LL> s = {x.min * y.min, x.max * y.max,
                    x.min * y.max, x.max * y.min};
    return {*min_element(s.begin(), s.end()), *max_element(s.begin(), s.end())};
}

P expression(int &i);
P term(int &i);
P power(int &i);
P number(int &i);
P digit(int &i);

P expression(int &i) {
    P res = term(i);
    while (i < n) {
        // dbg(i);
        if (s[i] == '+') {
            i++; res = res + term(i);
        } else if (s[i] == '-') {
            i++; res = res - term(i);
        } else break;
    }
    return res;
}

P term(int &i) {
    P res = power(i);
    while (i < n) {
        if (s[i] == '*') {
            i++; res = res * power(i);
        } else break;
    }
    return res;
}

P power(int &i) {
    P res = number(i);
    if (i < n && s[i] == 'd') {
        i++;
        P t = power(i);
        t.min = 1;
        res = res * t;
    }
    return res;
}

P number(int &i) {
    if (s[i] == '(') {
        i++;
        P res = expression(i);
        assert (s[i] == ')'); i++;
        return res;
    }
    return digit(i);
}

P digit(int &i) {
    LL r = 0;
    while (i < n && isdigit(s[i])) {
        r = r * 10 + s[i] - '0';
        i++;
    }
    return {r, r};
}

int main() {
    while (~scanf("%s", s)) {
        n = strlen(s);
        int pos = 0;
        auto ans = expression(pos);
        printf("%lld %lld\n", ans.min, ans.max);
    }
}
