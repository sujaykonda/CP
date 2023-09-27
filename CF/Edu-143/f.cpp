#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    adjlist adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b);
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int k; rd(k);
    vector<int> a(k); rd(a);
    
}

int main() {
    int t; rd(t);
    while(t--) tc();
}