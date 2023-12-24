#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int N, M; cin >> N >> M;
    vector<vector<pair<int, int>>> adj(N);
    for(int i = 0; i < M; i++) {
        int a, b, l; cin >> a >> b >> l;
        a--, b--;
        adj[a].push_back({l, b});
    }
    vector<bool> done(N);
    vector<int> o;
    function<void(int)> dfs = [&] (int s) {
        done[s] = true;
        for(auto [u, v] : adj[s]) {
            if(!done[v]) {
                dfs(v);
            }
        }
        o.push_back(s);
    };
    for(int i = 0; i < N; i++) if(!done[i]) dfs(i);
    vector<int> dp(N);
    for(int i : o) {
        for(auto [u, v] : adj[i]) {
            dp[i] = max(dp[i], dp[v] + 1);
        }
    }
    vector<vector<int>> b(N);
    for(int i = 0; i < N; i++) b[dp[i]].push_back(i);
    vector<ll> sm(N);
    vector<pair<int, int>> pick(N);

    vector<int> ro(N);
    for(int i = 0; i < b[0].size(); i++) ro[b[0][i]] = i;

    for(int i = 1; i < N; i++) {
        for(int s : b[i]) {
            pick[s] = {1e9, 1e9};
            for(auto [u, v] : adj[s]) {
                if(dp[v] == i - 1) {
                    pick[s] = min(pick[s], {u, ro[v]});
                }
            }
            sm[s] = sm[b[i - 1][pick[s].second]] + pick[s].first;
        }
        sort(b[i].begin(), b[i].end(), [&] (int a, int b) {
            return pick[a] < pick[b];
        });
        for(int j = 0; j < b[i].size(); j++) ro[b[i][j]] = j;
    }
    for(int i = 0; i < N; i++) cout << dp[i] << " " << sm[i] << endl;
}