#include <bits/stdc++.h>
using namespace std;

const int MX = 1 << 13;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++)
            cin >> a[i];
        vector<vector<bool>> dp(n + 1, vector<bool>(MX));
        vector<vector<bool>> done(n + 1, vector<bool>(n + 1));
        dp[0][0] = true;
        done[0][0] = true;
        for(int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1];
            int mex = 0;
            vector<bool> in(n);
            for(int j = i - 1; j >= 0; j--) {
                in[a[j]] = true;
                if(mex == a[j]) {
                    while(in[mex]) mex++;
                    if(!done[j][mex]) {
                        for(int k = 0; k < MX; k++) {
                            if(dp[j][k])
                                dp[i][k ^ mex] = true;
                        }
                        done[j][mex] = true;
                    }
                }
            }
        }
        int mx = 0;
        for(int i = 0; i < MX; i++) 
            if(dp[n][i])
                mx = i; 
        cout << mx << endl;
    }
}