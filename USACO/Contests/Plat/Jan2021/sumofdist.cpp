#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MXN = 1e5 + 1;
const int MOD = 1e9 + 7;
array<array<array<int, 2>, 2>, MXN + 1> dp;

void graph() {
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    vector<array<int, 2>> d(N, {MXN, MXN});
    queue<pair<int, int>> q;
    d[0][0] = 0; q.push({0, 0});
    while(!q.empty()) {
        int s = q.front().first, v = q.front().second + 1;
        q.pop();
        for(int u : adj[s]) {
            if(d[u][v % 2] == MXN) {
                d[u][v % 2] = v;
                q.push({u, v});
            }
        }
    }
    vector<vector<int>> mp(2 * N + 1);
    for(int i = 0; i < N; i++) {
        if(d[i][0] < MXN) mp[d[i][0]].push_back(d[i][1]);
        if(d[i][1] < MXN) mp[d[i][1]].push_back(d[i][0]);
    }
    vector<array<array<int, 2>, 2>> ndp(2 * N + 1, {{}});
    auto apply = [&] (int par) {
        int cnt0 = 0, cnt1 = 0;
        vector<int> rem(2 * N + 1);
        for(int i = par; i <= 2 * N; i += 2) {
            if(i - 1 >= 0)
                cnt1 -= rem[i - 1], cnt0 += rem[i - 1];
            for(int a : {0, 1}) 
                for(int b : {0, 1})
                    ndp[i][a][b] = (ndp[i][a][b] + (ll)cnt0 * dp[i][a][b]) % MOD;
            for(int a : {0, 1})
                for(int b : {0, 1})
                    ndp[i][a][1] = (ndp[i][a][1] + (ll)cnt1 * dp[i][a][b]) % MOD;
            
            
            for(int j : mp[i]) {

                if(j > i) {
                    for(int a : {0, 1}) 
                        for(int b : {0, 1})
                            ndp[i][1][1] = (ndp[i][1][1] + dp[i][a][b]) % MOD;
                    
                    cnt1++; 
                    if(j < MXN) 
                        rem[j]++;
                } else {
                    for(int a : {0, 1}) 
                        for(int b : {0, 1})
                            ndp[i][1][b] = (ndp[i][1][b] + dp[i][a][b]) % MOD;
                    cnt0++;
                }
            }
        }
        if(par == 0) par = 2;
        for(int i = 2 * N + par; i < MXN; i += 2) {
            array<array<int, 2>, 2> ndpsm {};
            for(int a : {0, 1}) 
                for(int b : {0, 1})
                    ndpsm[a][b] = (ndpsm[a][b] + (ll)cnt0 * dp[i][a][b]) % MOD;
            for(int a : {0, 1})
                for(int b : {0, 1})
                    ndpsm[a][1] = (ndpsm[a][1] + (ll)cnt1 * dp[i][a][b]) % MOD;
            dp[i] = ndpsm;
        }
    };
    apply(0), apply(1);
    for(int i = 0; i < ndp.size(); i++) dp[i] = ndp[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for(int i = 0; i < MXN; i++) dp[i][0][0] = 1;
    int K; cin >> K;
    for(int i = 0; i < K; i++) graph();
    int ans = 0;
    for(int i = 0; i < MXN; i++) {
        ans = (ans + (ll)i * dp[i][1][1]) % MOD;
    }
    cout << ans << endl;
}