#include <cplib/general.h>
using namespace std;

int main() {
    int n, d; rd(n, d);
    
    adjlist adj(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b);
        adj[a].pb(b), adj[b].pb(a);
    }
    vector<array<bool, 2>> inseq(n + 1);
    int m1; rd(m1);
    for(int i = 0; i < m1; i++) { 
        int ai; rd(ai); inseq[ai][1]; }
    int m2; rd(m2);
    for(int i = 0; i < m1; i++) { 
        int ai; rd(ai); inseq[ai][1]; }
    
    auto dfs = [&] (int s, int e, auto&& dfs) {
        for(int u : adj[s])
            if(u != e)
                dfs(u, s, dfs);
    };
}