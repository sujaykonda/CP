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

int n, m, q; 
vector<vector<pair<int, int>>> adj;
vector<int> sol;

void bfs(int k) {
    vector<int> d(n, -1);
    queue<int> q;
    d[0] = 0, q.push(0);
    while(!q.empty()) {
        int s = q.front(); q.pop();
        for(auto &[u, v] : adj[s])
            if(v <= k && d[u] == -1)
                d[u] = d[s] + 1, q.push(u);
    }
    for(int i = 0; i < n; i++)
        sol[k] = max(sol[k], d[i]);
}

void dc(int l, int r) {
    if(r - l <= 1) return;
    if(sol[l] <= 2 * sol[r]) {
        for(int i = l + 1; i < r; i++)
            sol[i] = sol[l];
    } else {
        int m = (l + r) / 2;
        bfs(m);
        dc(l, m), dc(m, r);
    }
}

int main() {
    cin >> n >> m >> q;
    adj.resize(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb({b, 0});
        adj[b].pb({a, 0});
    }
    for(int i = 1; i <= q; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb({b, i});
        adj[b].pb({a, i});
    }
    sol.resize(q + 1);
    bfs(0), bfs(q);
    dc(0, q);
    for(int i = 0; i <= q; i++)
        cout << sol[i] << '\n';
    cout << endl;
}