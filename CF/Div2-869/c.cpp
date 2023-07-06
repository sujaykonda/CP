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

struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
    int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
    int lb(ll x) {
        ll s = 0, p = 0;
        for(int i = lg(tree.size()); i >= 0; i--)
            if(p + (1 << i) < tree.size() && s + tree[p + (1 << i)] < x)
                p += (1 << i), s += tree[p];
        return p + 1;
    }
};

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n); cin >> a;
    vector<bool> pres(n, true);
    BIT bit(n);
    for(int i = 2; i < n; i++) {
        if(a[i - 2] >= a[i - 1] && a[i - 1] >= a[i])
            bit.add(i + 1, -1), pres[i] = false;
    }
    vector<vector<pair<int, int>>> queries(n);
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries[l - 1].pb({r, i});
    }
    vector<int> ans(q);
    for(int i = 0; i < n; i++) {
        for(auto &[u, v] : queries[i]) {
            ans[v] = u - i + (bit.sum(u) - bit.sum(i));
        }
        if(i < n - 2) {
            if(!pres[i + 2]) {
                pres[i + 2] = true;
                bit.add(i + 3, 1);
            }
        }
    }
    for(int i = 0; i < q; i++) cout << ans[i] << endl;
}