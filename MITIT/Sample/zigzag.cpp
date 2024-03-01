#include <cplib/math/mint.h>
using namespace std;
const int MOD = 998244353;
int main() {
    int N; rd(N);
    adjlist adj(N);
    for(int i = 0; i < N; i++) {
        int a, b; rd(a, b);
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<int> sz(N);
    vector<vector<mint<MOD>>> dp(N);
    function<void(int, int, int)> dfs = [&] (int s, int e, int c) {
        for(int u : adj[s]) {
            if(u != e) {
                dfs(u, s, c^1);
                if(sz[s] == 0) {
                    dp[s] = dp[u];
                } else {

                }
                sz[s] += sz[u];
            }
        }
        sz[s]++;
        if(sz[s] == 1) {
            dp[s] = {1};
        } else {
            if(c) {
                dp[s].pb(mint<MOD>(0));
                for(int i = sz[s] - 2; i >= 1; i--) {
                    dp[s][i] += dp[s][i + 1];
                }
            } else {
                dp[s].insert(dp[s].begin(), 0);
                for(int i = 1; i < sz[s]; i++) {
                    dp[s][i] += dp[s][i - 1];
                }
            }
        }
    };
    Comb<MOD> comb(N);
    
}