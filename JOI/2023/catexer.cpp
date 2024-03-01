#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int N; cin >> N;
    vector<int> P(N + 1), revP(N + 1);
    for(int i = 1; i <= N; i++) cin >> P[i], revP[P[i]] = i;
    vector<vector<int>> adj(N + 1);
    for(int i = 0; i < N - 1; i++) {
        int A, B; cin >> A >> B;
        adj[A].push_back(B);
        adj[B].push_back(A);
    }
    vector<vector<int>> jmp(N + 1, vector<int>(20));
    vector<int> dep(N + 1);
    function<void(int, int)> dfs = [&] (int s, int e) {
        jmp[s][0] = e;
        dep[s] = dep[e] + 1;
        for(int i = 0; i < 19; i++) {
            jmp[s][i + 1] = jmp[jmp[s][i]][i];
        }
        for(int u : adj[s]) if(u != e) dfs(u, s);
    };
    dfs(1, 0);
    auto lca = [&] (int a, int b) {
        if(dep[a] < dep[b]) swap(a, b);
        for(int i = 19; i >= 0; i--) {
            if(dep[jmp[a][i]] >= dep[b])
                a = jmp[a][i];
        }
        if(a == b) return a;
        for(int i = 19; i >= 0; i--) {
            if(jmp[a][i] != jmp[b][i]) {
                a = jmp[a][i];
                b = jmp[b][i];
            }
        }
        return jmp[a][0];
    };
    auto dist = [&] (int s, int t) {
        return dep[s] + dep[t] - 2 * dep[lca(s, t)];
    };
    vector<int> e(N + 1, -1);
    function<int(int)> get = [&] (int s) {
        return e[s] < 0 ? s : (e[s] = get(e[s]));
    };
    vector<ll> dp(N + 1);
    for(int i = 1; i <= N; i++) {
        int s = revP[i];
        for(int u : adj[s]) {
            if(P[u] <= i) {
                int g = get(u);
                dp[s] = max(dp[s], dist(s, g) + dp[g]);
                e[s] += e[g];
                e[g] = s;
            }
        }
    }
    cout << dp[revP[N]] << endl;
}