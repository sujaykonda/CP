#include <cplib/general.h>
using namespace std;

int main() {
    int n, m; rd(n, m);
    vector<int> p(n); rd(p);
    adjlist adj(n + 1);
    for(int i = 0; i < m; i++) {
        int a, b; rd(a, b); a--, b--;
        adj[b].pb(a);
    }
    vector<int> indeg(n);
    for(int i = 0; i < n; i++) for(int u : adj[i]) indeg[u]++;
    for(int i = 0; i < n; i++) if(indeg[i] == 0) adj[n].pb(i), indeg[i]++;
    for(int i = 0; i < n; i++) {
        int j = n + 1;
        queue<int> q; q.push(n);
        vector<vector<int>> lock(n + 1);
        vector<int> curindeg = indeg;
        curindeg[i] = 0;
        while(!q.empty()) {
            int s = q.front(); q.pop();
            j--;
            for(int u : adj[s]) {
                curindeg[u]--;
                if(curindeg[u] == 0) {
                    if(p[u] >= j)
                        q.push(u);
                    else
                        lock[p[u]].pb(u);
                }
            }
            for(int u : lock[j]) q.push(u);
        }
        cout << j << " ";
    }
    cout << endl;
}