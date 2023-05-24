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
 
struct MP {
    int a = 0, d = 0, mn = 0, nmn = 0; map<int, int> mp;
    void merge(MP& o) {
        int diff = mn + a + 1;
        a += o.mn + o.a + 1;
        for(auto [_u, _v] : o.mp) {
            int u = _u ^ o.d, v = _v + o.a;
            if(mp.count(u ^ d)) {
                if(v == o.mn + o.a) 
                    nmn = min(nmn, --mp[u ^ d]);
            } else {
                mp[u ^ d] = v + diff - a;
                nmn = min(nmn, mp[u ^ d]);
            }
        }
    }
};
 
vector<vector<int>> adj;
vector<int> a;
 
MP dfs(int s, int e) {
    MP res;
    vector<MP> mps;
    for(int u : adj[s])
        if(u != e)
            mps.emplace_back(dfs(u, s));
    if(mps.size() == 0) res.mp[0] = 0, res.mn = 0;
    else {
        sort(mps.begin(), mps.end(), [&] (MP& a, MP& b) { return a.mp.size() > b.mp.size(); });
        swap(res, mps[0]);
        for(int i = 1; i < mps.size(); i++)
            res.merge(mps[i]);
    }
    res.d ^= a[s];
    res.mn = res.nmn;
    return res;
}
 
int main() {
    int n; cin >> n;
    a.resize(n); cin >> a;
    adj.resize(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b), adj[b].pb(a);
    }
    MP res = dfs(0, -1);
    int best = res.mn + res.a + 1;
    if(res.mp.count(res.d)) best = min(best, res.mp[res.d] + res.a);
    cout << best << endl;
}