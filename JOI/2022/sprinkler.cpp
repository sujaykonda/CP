#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, L; cin >> N >> L;
    vector<vector<int>> adj(N);
    for(int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> p(N);
    function<void(int, int)> dfs = [&] (int s, int e) {
        p[s] = e;
        for(int u : adj[s]) {
            if(u != e) {
                dfs(u, s);
            }
        }
    };  
    dfs(0, -1);
    vector<int> h(N);
    for(int i = 0; i < N; i++) cin >> h[i];
    vector<vector<int>> mult(N, vector<int>(41, 1));
    int Q; cin >> Q;
    for(int i = 0; i < Q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int x, d, w; cin >> x >> d >> w; x--;
            for(int i = 0; i <= d; i++) {
                if(d - i > 0) mult[x][d - i - 1] = ((long long)mult[x][d - i - 1] * w) % L; 
                mult[x][d - i] = ((long long)mult[x][d - i] * w) % L; 
                if(p[x] == -1) {
                    for(int j = 0; j < d - i - 1; j++) mult[x][j] = ((long long)mult[x][j] * w) % L; 
                    break;
                }
                x = p[x];
            }
        } else {
            int x; cin >> x; x--;
            int ans = h[x];
            for(int i = 0; i <= 40; i++) {
                ans = ((long long)ans * mult[x][i]) % L;
                x = p[x];
                if(x == -1) break;
            }
            cout << ans << endl;
        }
    }
}