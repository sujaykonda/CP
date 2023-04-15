#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
vector<int> subdp;
vector<int> outdp;

void dfs(int s, int e) {
    for(int u : adj[s])
        if(u != e)
            dfs(u, s);
    for(int u : adj[s])
        if(u != e)
            subdp[s] = max(subdp[s], 1 + subdp[u]);
}

void dfs2(int s, int e) {
    int best = -1;
    for(int u : adj[s])
        if(u != e)
            if(best == -1 || subdp[best] < subdp[u])
                best = u;
    int best2 = -1;
    for(int u : adj[s]) {
        if(u != e && u != best) {
            outdp[u] = max(subdp[best] + 1, outdp[s]) + 1;
            if(best2 == -1 || subdp[best2] < subdp[u])
                best2 = u;
        }
    }
    if(best != -1) {
        outdp[best] = outdp[s] + 1;
        if(best2 != -1)
            outdp[best] = max(outdp[best], subdp[best2] + 2);
    }
    for(int u : adj[s])
        if(u != e)
            dfs2(u, s);
}  


int main() {
    cin >> n;
    adj.resize(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    subdp.resize(n + 1);
    dfs(1, 0);
    outdp.resize(n + 1);
    dfs2(1, 0);
    for(int i = 1; i <= n; i++)
        cout << max(subdp[i], outdp[i]) << " ";
    cout << endl;
}