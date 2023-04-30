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

const int M = 998244353;

vector<bool> imp;
vector<int> ans;
vector<vector<int>> adj;

void dfs(int s, int e, int t) {
    imp[s] = s == t;
    for(int u : adj[s])
        if(u != e)
            dfs(u, s, t), imp[s] = imp[s] || imp[u];
}
void dfs2(int s, int e, int cnt) {
    ans[s] = (ll)adj[s].size() * cnt % M;
    for(int u : adj[s])
        if(u != e)
            dfs2(u, s, cnt + imp[u]);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, s, t; cin >> n >> s >> t;
    adj.resize(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    imp.resize(n + 1);
    dfs(t, 0, s);
    ans.resize(n + 1);
    dfs2(t, 0, 0);
    ans[t] = 1;
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << endl;
}
