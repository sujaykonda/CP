#include <bits/stdc++.h>
using namespace std;

void tc() {
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // calc distances
    vector<array<int, 2>> d(N, {-1, -1});
    d[0][0] = 0;
    queue<pair<int, int>> q; q.push({0, 0});
    while(!q.empty()) {
        int s = q.front().first, v = q.front().second + 1; 
        q.pop();
        for(int u : adj[s]) {
            if(d[u][v % 2] == -1) {
                d[u][v % 2] = v; 
                q.push({u, v});
            }
        }
    }
    // tree case
    if(d[0][1] == -1) {
        int cnt = 0;
        for(int i = 0; i < N; i++) cnt += (d[i][0] != -1 || d[i][1] != -1);
        cout << cnt - 1 << endl;
        return;
    }
    map<int, map<int, int>> smmp;
    for(int i = 0; i < N; i++) 
        if(d[i][0] != -1) 
            smmp[d[i][0] + d[i][1]][min(d[i][0], d[i][1])]++;
    set<pair<int, int>> done;
    int ans = 0;
    for(auto& [sm, mp] : smmp) {
        int pdone = 0;
        for(int a = 0; a <= sm / 2; a++) {
            if(mp[a] == 0) { assert(pdone == 0); continue; } 
            if(done.count({a - 1, sm - a - 1})) {
                ans += mp[a] - pdone;
                mp[a] = pdone;
            } 
            if(mp[a] > 0){
                if(a + 1 == sm - a) {
                    if(a > 0)
                        ans += mp[a] - pdone;
                    ans += (mp[a] / 2) + (mp[a] % 2);
                } else {
                    if(a > 0)
                        ans += mp[a] - pdone;
                    ans += mp[a];
                    pdone = min(mp[a + 1], mp[a]);
                }
                mp[a] = 0;
            }
            done.insert({a, sm - a});
        }
    }
    cout << min(M, ans) << endl;
}

int main() {
    int T; cin >> T;
    while(T--) tc();
}