#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MXN = 3e5 + 1;
const int MOD = 998244353;
vector<int> adj[MXN];

pair<int, int> dfs(int s, int e) {
    int sm = 0;
    pair<int, int> dp = {0, 0};
    for(int u : adj[s]) {
        if(u != e) {
            auto ndp = dfs(u, s);
            dp.first += (ll)(1 + dp.first) * ndp.first % MOD;
            sm += ndp.first;
            sm %= MOD;
            dp.first %= MOD;
            dp.second += ndp.second;
            dp.second %= MOD;
        }
    }
    dp.second += sm;
    dp.second %= MOD;
    dp.first++;
    dp.first %= MOD;
    return dp;
}

void tc() {
    int n; cin >> n;
    for(int i = 1; i <= n; i++) adj[i].clear();
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto res = dfs(1, 0);
    cout << (1 + res.first + res.second) % MOD << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    while(t--) tc();
}