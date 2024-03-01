#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
using ll = long long;
int bpow(int a, ll p) { return (p == 0) ? 1 : (((ll)bpow(((ll)a * a) % MOD, p / 2) * (p & 1 ? a : 1)) % MOD); }

void tc() {
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    vector<int> pe(N);
    for(int i = 0; i < N; i++) cin >> pe[i];
    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> inv(N);
    for(int i = 1; i < N; i++) inv[i] = bpow(i, MOD - 2);
    vector<int> p(N), dep(N), preach(N);
    vector<bool> done(N);
    vector<pair<int, int>> be;
    function<void(int)> dfs = [&] (int s) {
        int cnt = 0;
        for(int u : adj[s]) cnt += !done[u];
        for(int u : adj[s]) {
            if(done[u]) {
                if(u != p[u]) {
                    // backedge
                    be.push_back({s, u});
                }
            } else {
                done[u] = true;
                p[u] = s;
                preach[u] = (ll)((ll) preach[s] * (1 + MOD - p[s]) % MOD) * inv[cnt] % MOD;
                dep[u] = 1 + dep[s];
                dfs(u);
            }
        }
    };
    done[0] = true;
    p[0] = -1;
    preach[0] = 1;
    dep[0] = 0;
    dfs(0);

    //for(int i = 0; i < ans.size() - 1; i++) cout << ans[i] << " ";
    //cout << ans.back() << endl;
}

int main() {
    int T; cin >> T;
    while(T--) tc();
}