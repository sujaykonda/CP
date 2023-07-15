#include <cplib/math/mint.h>
using namespace std;
const int MOD = 1e9 + 7;

int n; 
adjlist adj;

int dfs(int s, int e, mint<MOD>& sm) {
    int d = 1;
    for(int u : adj[s])
        if(u != e)
            d = max(d, dfs(u, s, sm) + 1);
    sm += d;
    return d;
}

void tc() {
    rd(n);
    adj = adjlist(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b);
        adj[a].pb(b), adj[b].pb(a);
    }
    mint<MOD> sm;
    dfs(1, 0, sm);
    sm *= bpow(mint<MOD>(2), n - 1);
    cout << sm.v << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}