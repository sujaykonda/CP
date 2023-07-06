#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

void dfs(int s, vector<vector<int>>& layers, vector<int>& ans, bool first) {
    if(s == layers.size()) return;
    if(first)
        dfs(s + 1, layers, ans, first);
    for(int v : layers[s])
        ans.push_back(v);
    dfs(s + 1, layers, ans, false);
}

void testcase() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[b].pb(a);
    }
    if(n == 1) {
        cout << "FINITE\n1\n1\n";
        return;
    }
    vector<bool> done(n + 1);
    vector<vector<int>> layers;
    layers.pb({1}); done[1] = true;
    while(layers.back().size() > 0) {
        vector<int> nlayer;
        for(int s : layers.back()) {
            for(int u : adj[s]) {
                if(!done[u])
                    nlayer.push_back(u), done[u] = true;
            }
        }
        layers.emplace_back(nlayer);
    }
    bool inf = false;
    for(int i = 1; i <= n; i++)
        if(!done[i])
            inf = true;
    
    if(inf) { 
        cout << "INFINITE\n";
        return;
    }
    vector<int> ans;
    dfs(0, layers, ans, true);
    cout << "FINITE\n";
    cout << ans.size() << endl;
    for(int v : ans)
        cout << v << " ";
    cout << "\n";
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}