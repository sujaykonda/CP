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


vector<vector<int>> adj;
vector<ll> a, imp;
vector<int> sz, p;

struct compare {
    bool operator()(int a, int b) const {
        if(sz[a] == sz[b]) return a < b;
        else return sz[a] > sz[b];
    }
};
vector<set<int, compare>> sortedadj;

void dfs(int s, int e) {
    p[s] = e;
    for(int u : adj[s])
        if(u != e)
            dfs(u, s);
    imp[s] = a[s], sz[s] = 1;
    for(int u : adj[s])
        imp[s] += imp[u], sz[s] += sz[u];
    for(int u : adj[s])
        if(u != e)
            sortedadj[s].insert(u);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, m; cin >> n >> m;
    a.resize(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    adj.resize(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].pb(b), adj[b].pb(a);
    }
    sz.resize(n + 1);
    imp.resize(n + 1);
    p.resize(n + 1);
    sortedadj.resize(n + 1);
    dfs(1, 0);
    for(int i = 0; i < m; i++) {
        int t, x; cin >> t >> x;
        if(t == 1) cout << imp[x] << endl;
        else if(t == 2) {
            if(sortedadj[x].size() == 0) continue;
            int par = p[x];
            sortedadj[par].erase(x);
            int son = *sortedadj[x].begin();
            sortedadj[x].erase(sortedadj[x].begin());
            int oldsz = sz[x];
            ll oldimp = imp[x];
            sz[x] -= sz[son];
            imp[x] -= imp[son];
            sz[son] = oldsz, imp[son] = oldimp;
            sortedadj[son].insert(x);
            p[x] = son;
            sortedadj[par].insert(son);
            p[son] = par;
        }
    }

}