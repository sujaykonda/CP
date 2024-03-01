#include <cplib/bs.h>
using namespace std;

int main() {
    int N, M; rd(N, M);
    vector<vector<pair<int, int>>> adj(N + 1);
    vector<int> e;
    for(int i = 0; i < M; i++) {
        int a, b, c; rd(a, b, c);
        adj[a].pb({b, c});
        adj[b].pb({a, c});
        e.pb(c);
    }
    int ans = 2e9;
    for(int i = 1; i <= N; i++) {
        if(adj[i].size() >= 2) {
            int v1 = 1e9, v2 = 1e9;
            for(auto [u, v] : adj[i]) {
                if(v < v1) v2 = v1, v1 = v;
                else if(v < v2) v2 = v;
            }
            ans = min(ans, v1 + v2);
        }
    }
    sort(e.begin(), e.end());
    e.push_back(2e9);
    cout << min(ans, e[bsmax(0, M, [&] (int x) {
        x = e[x];
        vector<int> cc(N + 1, -1);
        function<bool(int, int)> dfs = [&] (int s, int c) {
            cc[s] = c;
            for(auto [u, v] : adj[s]) {
                if(v < x) {
                    if(cc[u] != -1) {
                        if(cc[u] != c^1) {
                            return false;
                        }
                    } else {
                        if(!dfs(u, c^1)) return false;
                    }
                }
            }
            return true;
        };
        for(int i = 1; i <= N; i++) {
            if(cc[i] == -1) {
                if(!dfs(i, 0)) return false;
            }
        }
        return true;
    })]) << endl;
}