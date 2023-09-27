#include <cplib/general.h>
using namespace std;

int t; 
void tc() {
    int n; rd(n);
    adjlist adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b);
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    if(n == 1) {
        cout << 1 << endl;
        return;
    }
    if(n == 2) {
        cout << 2 << endl;
        return;
    }
    multiset<int> mcnts;
    vector<int> cnts(n), c(n);
    function<void(int, int)> dfs = [&] (int s, int e) {
        for(int u : adj[s]) {
            if(u != e)  
                dfs(u, s);
        }
        int mnc = -1;
        for(int u : adj[s]) {
            if(u != e) {
                if(mnc == -1 || cnts[mnc] > cnts[c[u]]) 
                    mnc = c[u];
            }
        }
        if(mnc == -1) {
            c[s] = s;
            cnts[s]++;
            mcnts.insert(1);
        } else {
            c[s] = mnc;
            mcnts.erase(mcnts.find(cnts[mnc]));
            cnts[mnc]++;
            mcnts.insert(cnts[mnc]);
        }
    };
    int rt = 0;
    while(adj[rt].size() == 1) rt++;
    dfs(rt, -1);
    int best = 0;
    auto change = [&] (int s, int nc) {
        if(c[s] == nc) return;
        mcnts.erase(mcnts.find(cnts[c[s]]));
        cnts[c[s]]--;
        mcnts.insert(cnts[c[s]]);
        c[s] = nc;
        mcnts.erase(mcnts.find(cnts[c[s]]));
        cnts[c[s]]++;
        mcnts.insert(cnts[c[s]]);
    };
    function<void(int, int)> dfs2 = [&] (int s, int e) {
        int cdec = c[s];
        int cinc = -1;
        for(int u : adj[s]) {
            if(cinc == -1 || cnts[cinc] - (cinc == cdec) > cnts[c[u]] - (c[u] == cdec))
                cinc = c[u];
        }
        int cinc2 = -1;
        for(int u : adj[s]) {
            if(c[u] != cinc && (cinc2 == -1 || cnts[cinc2] - (cinc2 == cdec) > cnts[c[u]] - (c[u] == cdec)))
                cinc2 = c[u];
        }
        change(s, cinc);
        best = max(best, *mcnts.lower_bound(1));
        for(int u : adj[s]) {
            if(u != e) {
                if(c[u] == cinc) {
                    assert(cinc2 != -1);
                    change(s, cinc2);
                }
                dfs2(u, s);
                change(s, cinc);
            }
        }
        change(s, cdec);
    };
    dfs2(rt, -1);
    cout << best << endl;
}

int main() {
    rd(t);
    while(t--) tc();
}