#include <bits/stdc++.h>
using namespace std;
const int MXN = 2e5 + 1;
const int MXLG = 19;
vector<pair<int, int>> adj[MXN]; 
bool done[MXN];
pair<int, int> jmp[MXN][MXLG];
int dep[MXN];
int bestw;
pair<int, int> best;
void dfs(int s) {
    done[s] = true;
    for(int i = 0; i < MXLG - 1; i++) {
        jmp[s][i + 1].first = jmp[jmp[s][i].first][i].first;
        jmp[s][i + 1].second = min(jmp[s][i].second, jmp[jmp[s][i].first][i].second);
    }
    for(auto [u, v] : adj[s]) {
        if(done[u]) {
            if(u != jmp[s][0].first && dep[u] < dep[s]) {
                int a = s;
                int mn = v;
                for(int i = MXLG - 1; i >= 0; i--) {
                    if(dep[u] <= dep[jmp[a][i].first]) {
                        mn = min(mn, jmp[a][i].second);
                        a = jmp[a][i].first;
                    }
                }
                if(mn < bestw) {
                    bestw = mn;
                    best = {s, u};
                }
            }
        } else {
            dep[u] = dep[s] + 1;
            jmp[u][0] = {s, v};
            dfs(u);
        }
    }
}

void tc() {
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n; i++) adj[i].clear();
    for(int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    for(int i = 1; i <= n; i++) done[i] = false;
    bestw = 1e9;
    best = {0, 0};
    vector<pair<int, int>> st;
    for(int i = 0; i < MXLG; i++) jmp[0][i] = {0, 1e9};
    dep[0] = -1;
    for(int i = 1; i <= n; i++) {
        if(!done[i]) {
            jmp[i][0] = {0, 1e9};
            dep[i] = 0;
            dfs(i);
        }
    }
    vector<int> cyc;
    int a = best.first, b = best.second;
    while(a != b) {
        cyc.push_back(a);
        a = jmp[a][0].first;
    }
    cyc.push_back(b);
    cout << bestw << " " << cyc.size() << '\n';
    for(int i : cyc) cout << i << " ";
    cout << endl;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) tc();
}