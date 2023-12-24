#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MX = 2e5 + 1;

vector<int> adj[MX];
bool done[MX];

int dfs(int s) {
    if(done[s]) return 0;
    done[s] = true;
    int sz = 1;
    for(int u : adj[s]) {
        sz += dfs(u);
    }
    return sz;
}

int main() {
    ll N, M;
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> szs;
    for(int i = 1; i < MX; i++) {
        if(!done[i]) {
            int sz = dfs(i);
            if(sz != 1) {
                szs.push_back(sz);
            }
        }
    }
    sort(szs.begin(), szs.end(), greater<int>());
    ll S = 0, sm = 0;
    for(int sz : szs) {
        S = max(S, sm + (ll)(sz - 1) * N + 1);
        sm += sz;
    }
    ll ans = S;
    for(int i : szs) ans -= i - 1;
    ans--;
    cout << ans << endl;
}