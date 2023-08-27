#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cplib/general.h>
using namespace std;

const int INF = 1e8;

void tc() {
    int n; rd(n);
    vector<int> c(n); rd(c);
    adjlist adj(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<int> p(n + 1), d(n + 1);
    function<void(int, int)> dfs = [&] (int s, int e) {
        p[s] = e;
        for(int u : adj[s])
            if(u != e)
                d[u] = d[s] + 1, dfs(u, s);
    };
    dfs(c[0], 0);
    int ans = n + 1;
    for(int i = 1; i < n; i++) {
        int up = 0, s = c[i];
        while(s != 0 && up < ans) {
            ans = min(ans, up + d[s]);
            d[s] = min(d[s], up);
            s = p[s];
            up++;
        }
        cout << ans << " ";
    }
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}