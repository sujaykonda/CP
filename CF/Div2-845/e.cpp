#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/graph/scc.h>
#include <cplib/bs.h>
using namespace std;

int n, m; 
wadjlist adj;
adjlist uwadj;
vector<int> weights;

vector<int> scc, comp, head;
adjlist compadj;
vector<bool> compdone;

void dfs(int s, int c) {
    comp[s] = c;
    for(int u : uwadj[s]) {
        if(comp[u] == -1) {
            dfs(u, c);
        } else if(comp[u] != c) {
            if(scc[head[comp[u]]] == scc[u]) {
                compadj[c].pb(comp[u]);
            }
        }
    }
}

void dfs2(int s) {
    compdone[s] = true;
    for(int u : compadj[s])
        if(!compdone[u]) dfs2(u);
}

bool check(ll i) {
    ll x = weights[i];
    uwadj = adjlist(n);
    for(int i = 0; i < n; i++) {
        for(auto [u, v] : adj[i])
            if(v <= x)
                uwadj[i].pb(u);
    }
    scc = comp = vector<int>(n, -1);
    int sccs = findSCC(scc, uwadj);
    int cc = 0; compadj.clear();
    head.clear();
    for(int i = 0; i < n; i++) {
        if(comp[i] == -1) {
            compadj.pb({});
            head.pb(i);
            dfs(i, cc++);
        }
    }
    compdone = vector<bool>(cc);
    dfs2(cc - 1);
    for(int i = 0; i < cc; i++) {
        if(!compdone[i]) return false;
    }
    return true;
}


void tc() {
    rd(n, m);
    adj = wadjlist(n);
    weights.clear();
    weights.pb(0);
    for(int i = 0; i < m; i++) {
        int a, b, c; rd(a, b, c); a--, b--;
        adj[a].pb({b, 0});
        adj[b].pb({a, c});
        weights.pb(c);
    }
    sort(weights.begin(), weights.end());
    //cout << check(1) << endl;
    int ans = bsmin(0, weights.size() - 1, check);
    cout << ((ans == weights.size()) ? -1 : weights[ans]) << '\n';
}

int main() {
    int t; rd(t);
    while(t--) tc();
}