#include <cplib/general.h>
using namespace std;

vector<vector<int>> adj;
int main() {
    int n; rd(n);
    adj.resize(n + 1);
    for(int i = 0; i < n - 1; i ++) {
        int a, b; rd(a), rd(b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    
    vector<vector<int>> rts(n + 1);
    for(int rt = 1; rt <= n; rt++) {
        vector<int> d(n + 1, -1);
        queue<int> q;
        d[rt] = 0; q.push(rt);
        while(!q.empty()) {
            int s = q.front();
            rts[rt].pb(d[s]);
            q.pop();
            for(int u : adj[s]) {
                if(d[u] == -1) {
                    d[u] = d[s] + 1;
                    q.push(u);
                }
            }
        }
    }

    vector<ll> ans(n + 1, 0);
    for(int rt = 1; rt <= n; rt++) {
        ll sm = 0;
        for(int i = 0; i < n; i++) {
            sm += rts[rt][i];
            ans[i + 1] = max(ans[i + 1], (ll) (i + 1) * (n - 1) - 2 * sm);
        }
    }
    for(ll a : ans) cout << a << " ";
    cout << endl;
}  