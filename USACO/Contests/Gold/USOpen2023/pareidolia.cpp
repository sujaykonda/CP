#include <bits/stdc++.h>
using namespace std;
using ll = long long;


void updmx(pair<int, int>& a, pair<int, int> b) { a = max(a, b); }

int main() {
    string s;
    cin >> s;
    int n = s.length();
    vector<int> cost(n);
    for(int i = 0; i < n; i++)
        cin >> cost[i];
    
    string tar = "bessie";
    vector<vector<pair<int, int>>> dp(n + 1,  vector<pair<int, int>>(6, {-1, 0}));
    dp[0][0] = {0, 0};
    for(int i = 0; i < n; i++) {
        dp[i + 1][0] = dp[i][0];
        for(int j = 0; j < 6; j++) {
            updmx(dp[i + 1][j], {dp[i][j].first, dp[i][j].second - cost[i]});
            if(s[i] == tar[j] && dp[i][j].first > -1) {
                updmx(dp[i + 1][(j + 1) % 6], {dp[i][j].first + (j == 5), dp[i][j].second});
            }
        }
    }
    cout << dp[n][0].first << endl;
    cout << -dp[n][0].second << endl;
}