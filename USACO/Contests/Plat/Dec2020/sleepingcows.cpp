#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;


int main() {
    int N; cin >> N;
    map<int, pair<int, int>> mp;
    for(int i = 0; i < N; i++) {
        int s; cin >> s; mp[s].first++;
    }
    for(int i = 0; i < N; i++) {
        int s; cin >> s; mp[s].second++;
    }
    vector<array<int, 2>> dp(N + 1); dp[0][0] = 1;
    for(auto [u, v] : mp) {
        int x = v.first, y = v.second;
        for(int k = 0; k < x; k++) {
            vector<array<int, 2>> ndp(N + 1);
            for(int i = N; i >= 0; i--) {
                if(i < N)
                    for(int j : {0, 1}) {
                        ndp[i + 1][j] = (ndp[i + 1][j] + (ll)(i + 1) * dp[i][j]) % MOD;
                        ndp[i][1] = (ndp[i][1] + dp[i][j]) % MOD;
                    }
            }
            dp = ndp;
        }
        for(int k = 0; k < y; k++) {
            vector<array<int, 2>> ndp(N + 1);
            for(int i = 0; i <= N; i++) {
                if(i > 0) {
                    ndp[i - 1][0] = (ndp[i - 1][0] + dp[i][0]) % MOD;
                    ndp[i - 1][1] = (ndp[i - 1][1] + dp[i][1]) % MOD;
                }
                ndp[i][0] = (ndp[i][0] + dp[i][0]) % MOD;
            }
            dp = ndp;
        }
    }
    cout << ((dp[0][0] + dp[0][1]) % MOD) << endl;
}