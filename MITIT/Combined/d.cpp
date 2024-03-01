#include <cplib/general.h>
using namespace std;

int main() {
    int T, X; rd(T, X);
    if(X == 0) {
        while(T--) {
            int N; rd(N);
            vector<int> a(N); rd(a);
            adjlist adj(N + 2);
            for(int i = 0; i < N; i++) {
                adj[i + 2].pb(a[i]);
            }
            vector<array<int, 2>> gdp(N + 2, {{0, 0}});
            vector<int> rdp(N + 2);
            function<void(int, int)> dfs = [&] (int s, int e) {
                for(int u : adj[s]) {
                    if(u != e) {
                        dfs(u, s);
                        rdp[s] += gdp[u][0];
                        gdp[s][1] = max(gdp[s][1], gdp[s][0] + gdp[u][0]);
                        gdp[s][1] = max(gdp[s][1], gdp[s][0] + rdp[u]);
                        gdp[s][1] = max(gdp[s][1], gdp[u][1]);
                        gdp[s][0] = max(gdp[s][0], rdp[u] + 1);
                        gdp[s][0] = max(gdp[s][0], gdp[u][0]);
                    }
                }
            };
            dfs(1, 0);
            cout << max({rdp[1], gdp[1][0], gdp[1][1]}) << endl;
        }
    }
}