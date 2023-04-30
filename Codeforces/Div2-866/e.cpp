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

vector<vector<int>> adj;
pair<int, int> dfs(int s, int e) {
    pair<int, int> mx = {0, s};
    for(int u : adj[s])
        if(u != e)
            mx = max(mx, dfs(u, s));
    mx.first++;
    return mx;
}

bool dfs2(int s, int e, int t, vector<int>& path) {
    path.pb(s);
    if(s == t) return true;
    for(int u : adj[s]) {
        if(u != e)
            if(dfs2(u, s, t, path))
                return true;
    }
    path.pop_back();
    return false;
}

int main() {
    int n; cin >> n;
    adj.resize(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    for(int i = 1; i <= n; i++) {
        if(adj[i].size() > 2) {
            int nonleaf = 0;
            for(int u : adj[i])
                nonleaf += adj[u].size() > 1;
            if(nonleaf > 2) {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
    int r1 = dfs(1, 0).second;
    int r2 = dfs(r1, 0).second;
    vector<int> dia;
    dfs2(r1, 0, r2, dia);
    set<int> dias;
    for(int s : dia) dias.insert(s);
    vector<int> path;
    for(int i = 0; i < dia.size(); i += 2) {
        if(i > 0) {
            for(int u : adj[dia[i - 1]])
                if(!dias.count(u))
                    path.pb(u);
        }
        path.pb(dia[i]);
    }
    for(int i = dia.size() - 2 + ((dia.size() - 1) % 2); i >= 0; i -= 2) {
        if(i < dia.size() - 1) {
            for(int u : adj[dia[i + 1]])
                if(!dias.count(u))
                    path.pb(u);
        }
        path.pb(dia[i]);
    }
    for(int s : path) cout << s << " ";
    cout << endl;
}