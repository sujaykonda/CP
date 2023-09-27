#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m; rd(n, m);
    vector<int> a(n); rd(a);
    adjlist adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; rd(u, v);
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int> d(n);
    for(int i = 0; i < n; i++) d[i] = adj[i].size();
    queue<int> q;
    for(int i = 0; i < n; i++) 
        if(d[i] == a[i]) q.push(i), d[i] = -1;
    vector<pair<int, int>> e;
    while(q.size() > 0) {
        int s = q.front(); q.pop();
        for(int u : adj[s]) {
            if(d[u] != -1) {
                d[u]--;
                e.push_back({s, u});
                if(d[u] == a[u]) {
                    q.push(u);
                    d[u] = -1;
                }
            }
        }
    }
    ll ans = ((ll)n * (n + 1)) / 2;
    for(int i = 0; i <= (n - 1) / 64; i++) {
        vector<ll> r(n);
        for(int j = 0; j < 64 && j < n - i * 64; j++) {
            r[i * 64 + j] = 1LL << j;
        }
        for(auto [u, v] : e) {
            r[v] |= r[u];
        }
        for(int j = 0; j < n; j++) {
            ans -= __builtin_popcountll(r[j]);
        }
    }
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}