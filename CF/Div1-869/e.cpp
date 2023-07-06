#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
// debug tools
string str(char c) { return string(1, c); } string str(_Bit_reference b) { return b ? "T" : "F"; }
string str(int x) { return to_string(x); } string str(ll x) { return to_string(x); }
string str(uint64_t x) { return to_string(x); }
template<class T> string str(T a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

const int MOD = 1e9 + 7;
const int MODINV2 = 5e8 + 4;
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

void testcase() {
    int n; cin >> n;
    vector<int> a(n); cin >> a;
    sort(a.begin(), a.end());
    if(n == 2) {
        cout << (a[1] - a[0]) % MOD << endl;
        return;
    }
    
    bint<1000031> best; 
    bint<1000031> left;
    left.add(n - 1, a[n - 1]);
    for(int i = n - 2; i >= 1; i--)
        left.add(i, a[i] - a[i + 1]);
    left.add(n - 1, -a[0]);

    if(left > best) best = left;
    int next = 0;
    for(int i = 1; i <= n / 2; i++) {
        left.add(i, a[i + 1] - a[i]);
        left.add(n - 1 - i, a[i - 1] - a[i]);
        if(a[i + 1] != a[i] && next < i) {
            if(left > best) best = left;
            next = n - i - 31;
        }
    }

    bint<1000031> right;
    right.add(n - 1, a[n - 1]);
    for(int i = 1; i < n - 1; i++)
        right.add(n - 1 - i, a[i - 1] - a[i]);
    right.add(n - 1, -a[0]);
    if(right > best) best = right;
    next = n - 1;
    for(int i = n - 2; i > n / 2; i--) {
        right.add(i, a[i] - a[i + 1]);
        right.add(n - 1 - i, a[i] - a[i - 1]);
        if(a[i] != a[i - 1] && i < next) {
            if(right > best) best = right;
            next = n - i + 31;
        }
    }
    
    int val = best.eval(MOD);
    for(int i = 0; i < n - 1; i++)
        val = ((ll)val * MODINV2) % MOD;
    cout << val << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}
