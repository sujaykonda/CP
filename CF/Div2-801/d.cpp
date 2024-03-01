#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    if(n == 1) {
        cout << 0 << endl;
        return;
    }
    adjlist adj(n);
    for(int i = 0; i < n - 1; i++) {
        int x, y; rd(x, y);
        x--, y--;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    vector<int> subdp(n);
    vector<int> used(n);
    function<void(int, int)> dfs = [&] (int s, int e) {
        subdp[s] = 0;
        for(int u : adj[s]) {
            if(u != e) {
                dfs(u, s);
                subdp[s] += max(1, subdp[u]);
                if(subdp[u] == 0) used[s] = 1;
            }
        }
        subdp[s] -= used[s];
    };
    dfs(0, -1);
    int bestdp = n;
    function<void(int, int, int)> dfs2 = [&] (int s, int e, int updp) {
        int cdp = 0;
        int cused = 0;
        if(e != -1) {
            cdp = max(1, updp);
            cused |= (updp == 0);
        } 
        reverse(adj[s].begin(), adj[s].end());
        vector<int> sdp;
        vector<int> sused;
        for(int u : adj[s]) {
            if(u != e) {
                sdp.pb(cdp);
                sused.pb(cused);
                cdp += max(1, subdp[u]);
                cused |= (subdp[u] == 0);
            }
        }
        bestdp = min(cdp - cused, bestdp);
        reverse(adj[s].begin(), adj[s].end());
        cdp = 0;
        cused = 0;
        for(int u : adj[s]) {
            if(u != e) {
                dfs2(u, s, cdp + sdp.back() - (cused | sused.back()));
                sdp.pop_back();
                sused.pop_back();
                cdp += max(1, subdp[u]);
                cused |= (subdp[u] == 0);
            }
        }
        
    };
    dfs2(0, -1, 0);
    cout << bestdp + 1 << endl;
}

int main() {
    int t; rd(t);
    while(t--) {
        tc();
    }
}