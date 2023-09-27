#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m, k; rd(n, m, k);
    vector<int> h(n); rd(h);
    adjlist radj(n), adj(n);
    vector<int> outdeg(n), indeg(n);
    for(int i = 0; i < m; i++) {
        int a, b; rd(a, b);
        a--, b--;
        radj[b].pb(a);
        adj[a].pb(b);
        outdeg[a]++;
        indeg[b]++;
    }
    vector<bool> done(n);
    vector<int> o;
    function<void(int)> dfs = [&] (int s) {
        for(int u : radj[s])
            if(!done[u])
                done[u] = true, dfs(u);
        o.pb(s);
    };
    for(int i = 0; i < n; i++) {
        if(!done[i]) done[i] = true, dfs(i);
    }
    reverse(o.begin(), o.end());
    vector<ll> dp(n);
    for(int i = 0; i < n; i++) {
        if(outdeg[i] == 0) dp[i] = 0;
    }
    for(int i : o) {
        for(int u : adj[i]) {
            dp[i] = max(dp[i], dp[u] + h[u] - h[i] + k * (h[u] < h[i]));
        }
    }
    ll start = k;
    ll end = 0;
    multiset<pair<int, int>> ms;
    for(int i = 0; i < n; i++) {
        if(indeg[i] == 0) start = min(start, (ll)h[i]), end = max(end, (ll)dp[i] + h[i]), ms.insert({h[i], i});
    }
    ll best = 1e18;
    for(auto [u, v] : ms) {
        best = min(best, end - u);
        end = max(end, dp[v] + h[v] + k);
    }
    cout << best << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}