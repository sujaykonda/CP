#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n'
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

template <int MOD> struct mint {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; }
    mint() : v(0) {}
    mint(long long _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
    mint& operator+=(mint o) { if((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { v += ((v -= o.v) < 0) * MOD; return *this; }
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
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n; cin >> n;
    vector<int> c(n); cin >> c;
    vector<vector<int>> ts(n);
    
    for(int i = 0; i < n; i++) {
        int t; cin >> t; t--; 
        ts[t].pb(i);
    }
     
    Comb<MOD> comb(n);
    vector<mint<MOD>> dp(n + 1);
    
    dp[0] = comb.f[n];
    for(int i = 0; i < n; i++) dp[0] *= comb.invf[c[i]];

    for(int t = 0; t < n; t++) {
        int tn = ts[t].size();
        vector<mint<MOD>> tdp(tn + 1); tdp[0] = 1;
        for(int i : ts[t])
            for(int j = tn - 1; j >= 0; j--)
                for(int k = 1; k <= tn - j && k <= c[i]; k++)
                    tdp[j + k] += tdp[j] * comb.f[c[i]] * comb.invf[c[i] - k] * comb.choose(tn - j, k);
        for(int i = n - 1; i >= 0; i--) {
            if(dp[i].v != 0) {
                for(int j = 1; j <= tn; j++) {
                    dp[i + j] += dp[i] * tdp[j] * comb.invf[n - i] * comb.f[n - i - j];
                }
            }
        }
    }
    mint<MOD> ans = 0;
    for(int i = 0; i <= n; i++)
        ans += (i % 2 ? -1 : 1) * dp[i];
    cout << ans.v << endl;
}
