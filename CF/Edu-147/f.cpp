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
#define $ << '\n'

template <int MOD> struct mint {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; }
    mint() : v(0) {}
    mint(long long _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
    mint& operator+=(mint o) { if((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { if((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(mint o) { v = int((long long) v * o.v % MOD); return *this; }
    mint& operator/=(mint o) { return (*this) *= inv(o);}
    friend mint pow(mint a, long long p) { assert(p >= 0); return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1); }
    friend mint inv(mint a) { return pow(a, MOD - 2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
    friend istream& operator>>(istream& is, mint& m) { is >> m.v; return is; }
    friend string str(mint a) { return to_string(a.v); }
    friend bool operator<(mint a, mint b) { return a.v < b.v; }
};

template <int MOD> struct Comb {
    vector<mint<MOD>> f, invf;
    Comb() : Comb(0) {}
    Comb(int n) : f(n + 1), invf(n + 1) {
        f[0] = 1;
        for (int i = 1; i <= n; i++)
            f[i] = f[i - 1] * i;
        invf[n] = inv(f[n]);
        for (int i = n; i >= 1; i--)
            invf[i - 1] = invf[i] * i;
    }
    mint<MOD> choose(int n, int k) { return (k > n) ? 0 : (f[n] * invf[k] * invf[n - k]); }
    mint<MOD> perm(int n, int k) { return (k > n) ? 0 : (f[n] * invf[n - k]); }
};

const int MOD = 998244353;

int main() {
    int n, m, k; cin >> n >> m >> k;
    if((ll)m * (k + 1) > n) { cout << 0 << '\n'; return 0; }
    Comb<MOD> comb(n);
    mint<MOD> ans = 0;
    for(int i = 0; i <= m; i++) {
        ans += pow(mint<MOD>(2), m) * pow(inv(mint<MOD>(-2)), i) * comb.choose(m, i) * comb.choose(n - (m + i) * k, m);
    }
    cout << str(ans) $;
}

// (n - km) choose m * 2 ^ m
// let f(x) = # of ways to construct m integers such that the first x are > 2k and the rest are > k and sum up to n
// = (n + m - x * (2k + 1) - (m - x) * (k + 1)) choose m
// = (n - 2kx - x - mk - m + xk + x) choose m
// = (n - (x + m)k) choose m
// note m + x must be < n / k
// let g(x) = # of ways to contruct m integers such that the first x are > 2k and the rest > k but < 2k and sum up to n (order matters)
// therefore the answer = sum when x is in [0, min(m, n / k - m)] of: g(x) * 2 ^ (m - x) * (m choose x)
// g(x) = sum when y is in [0, m - x] of: (-1) ^ y * f(x + y) * (m - x) choose y
