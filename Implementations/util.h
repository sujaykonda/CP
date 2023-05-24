#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T> struct RB {
    stack<pair<T*, T>> hist;
    void upd(T& ref, T val) { hist.push({&ref, ref}); ref = val; }
    void rb() { *hist.top().first = hist.top().second; hist.pop(); }
    int gett() { return hist.size(); }
};

template<size_t sz> struct bint {
    // every place will store a number from 0 to 2^63
    int hd = 0;
    array<uint64_t, (sz + 62) / 63> a{};
    void add(int k, int v) { if(v == 0) return; uint64_t x = abs(v);
        _sgnadd(k / 63, (x << (k % 63)) % (1ull << 63), v > 0);
        if(x >> (63 - (k % 63))) _sgnadd(k / 63 + 1, x >> (63 - (k % 63)), v > 0); }
    void _sgnadd(int k, uint64_t x, bool pos) { if(pos) _add(k, x); else _sub(k, x); }
    void _sub(int k, uint64_t x) { if(a[k] >= x) { a[k] -= x; return; }
        _sub(k + 1, 1); _add(k, (1ull << 63) - x); }
    void _add(int k, uint64_t x) { hd = max(hd, k); a[k] += x;
        if(a[k] >> 63) { a[k] -= (1ull << 63); _add(k + 1, 1); } }
    friend bool operator>(bint& a, bint& b) {
        for(int i = max(a.hd, b.hd); i >= 0; i--) {
            if(a.a[i] == b.a[i]) continue;
            return a.a[i] > b.a[i];
        }
        return false;
    }
    int eval(int m) {
        int v = 0, cur = 1;
        for(int i = 0; i < a.size(); i++) {
            v = (v + ((a[i] % m) * cur % m)) % m;
            cur = cur * ((1ull << 63) % m) % m;
        }
        return v;
    }
};
