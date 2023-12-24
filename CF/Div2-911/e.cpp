#include <cplib/general.h>
#include <cplib/graph/scc.h>
using namespace std;

void tc() {
    int n, m; rd(n, m);
    vector<int> a(n); rd(a);
    adjlist adj(n); 
    for(int i = 0; i < m; i++) {
        int a, b; rd(a, b);
        a--, b--;
        adj[a].pb(b);
    }
    vector<int> comp(n);
    int cc = findSCC(comp, adj);
    vector<int> sz(cc);
    vector<ll> val(cc);
    for(int i = 0; i < n; i++) {
        sz[comp[i]]++;
        val[comp[i]] += a[i];
    }
    adjlist radj(cc);
    for(int i = 0; i < n; i++) {
        for(int j : adj[i]) {
            if(comp[i] != comp[j]) {
                radj[comp[i]].pb(comp[j]);
            }
        }
    }
    vector<int> o;
    vector<bool> ndone(cc);
    function<void(int)> dfs2 = [&] (int s) {
        for(int u : radj[s]) {
            if(!ndone[u]) {
                ndone[u] = true;
                dfs2(u);
            }
        }
        o.pb(s);
    };

    for(int i = 0; i < cc; i++) {
        if(!ndone[i]) {
            ndone[i] = true;
            dfs2(i);
        }
    }
    vector<pair<int, ll>> dp(cc);
    for(int i : o) {
        dp[i] = {sz[i], -val[i]};
        for(int u : radj[i]) {
            dp[i] = max(dp[i], {dp[u].first + sz[i], dp[u].second - val[i]});
        }
    }
    pair<int, ll> mx = dp[0];
    for(int i = 0; i < cc; i++) mx = max(mx, dp[i]);
    cout << mx.first << " " << -mx.second << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}