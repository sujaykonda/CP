#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

int n; 
vector<vector<int>> adj;
vector<int> a;
vector<int> p;

void dfs(int s, int e) {
    p[s] = e;
    for(int u : adj[s])
        if(u != e)
            dfs(u, s);
}

void dfs2(int s, int e, int o, map<int, int>& mp, int& MAD) {
    mp[a[s]]++;
    if(mp[a[s]] == 2) MAD = max(MAD, a[s]); 
    for(int u : adj[s])
        if(u != e && u != o)
            dfs2(u, s, o, mp, MAD);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    adj.resize(n + 1);
    vector<pair<int, int>> edges;
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        edges.pb({a, b});
        adj[a].pb(b), adj[b].pb(a);
    }
    a.resize(n + 1);
    map<int, int> cnt;
    for(int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++;
    int MAD = 0;
    for(auto &[u, v] : cnt)
        if(v >= 2) MAD = u;
    if(MAD == 0) {
        for(int i = 0; i < n - 1; i++) 
            cout << 0 << endl;
        return 0;
    }
    if(cnt[MAD] > 2) {
        for(int i = 0; i < n - 1; i++) 
            cout << MAD << endl;
        return 0;
    }
    int st = 0, en = 0;
    for(int i = 1; i <= n; i++)
        if(a[i] == MAD)
            if(st == 0) st = i;
            else en = i;
    p.resize(n + 1);
    dfs(st, 0);
    vector<int> path;
    int cur = en;
    while(cur != st) path.pb(cur), cur = p[cur];
    vector<int> ans(n + 1, MAD);
    map<int, int> mp;
    int last = 0;
    dfs2(en, p[en], 0, mp, last);
    ans[en] = last;
    for(int i = 1; i < path.size(); i++) {
        dfs2(path[i], p[path[i]], path[i - 1], mp, last);
        ans[path[i]] = last;
    }
    mp.clear();
    last = 0;
    for(int i = path.size() - 1; i >= 0; i--) {
        dfs2(p[path[i]], p[p[path[i]]], path[i], mp, last);
        ans[path[i]] = max(ans[path[i]], last);
    }
    for(int i = 0; i < n - 1; i++) {
        if(p[edges[i].first] == edges[i].second)
            cout << ans[edges[i].first] << endl;
        else
            cout << ans[edges[i].second] << endl;
    }
}