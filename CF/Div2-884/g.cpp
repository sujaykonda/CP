#include <cplib/graph/tree.h>
using namespace std;

int main() {
    int n; rd(n);
    adjlist adj(n + 1);
    vector<pair<int, int>> edges;
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b); edges.pb({a, b});
        adj[a].pb(b), adj[b].pb(a);
    }
    LCA lca(adj);
    vector<int> L(n);
    vector<ll> d(n), de(n + 1);
    for(int i = 1; i < n; i++) rd(d[i]), L[i] = lca.q(i, i + 1);
    for(int j = 0; j <= 60; j++) {
        for(int i = 1; i < n; i++) {
            de[i + 1] = (d[i] - (de[i] % (1LL << (j + 1))) + (1LL << (j + 1)) + 2 * (de[L[i]] % (1LL << j))) % (1LL << (j + 1));
        }
    }
    for(auto& [u, v] : edges) {
        if(lca.dep[u] > lca.dep[v]) swap(u, v);
        if(de[v] - de[u] <= 0 || de[v] - de[u] > 1e12) {
            cout << -1 << '\n';
            return 0;
        }
    }
    
    for(auto& [u, v] : edges) cout << de[v] - de[u] << '\n';
}