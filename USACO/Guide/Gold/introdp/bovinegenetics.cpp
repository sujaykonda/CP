#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MODN = 1000000007;
int main() {
    string s;
    cin >> s;
    int n = s.length();
    vector<int> seq(n);
    for(int i = 0; i < n; i++)
        if(s[i] == 'A') seq[i] = 0;
        else if(s[i] == 'G') seq[i] = 1;
        else if(s[i] == 'C') seq[i] = 2;
        else if(s[i] == 'T') seq[i] = 3;
        else seq[i] = 4;
    
    vector<vector<vector<ll>>> b(4, vector<vector<ll>>(4, vector<ll>(4)));
    vector<array<ll, 4>> dp(n + 1, {0, 0, 0, 0});
    dp[0][0] = dp[0][1] = dp[0][2] = dp[0][3] = 1;
    for(int i = 0; i < n; i++) {
        vector<vector<vector<ll>>> nb(4, vector<vector<ll>>(4, vector<ll>(4)));
        for(int c = 0; c < 4; c++) {
            if(seq[i] == c || seq[i] == 4) {
                dp[i + 1][c] = (dp[i + 1][c] + dp[i][c]) % MODN;
                for(int c2 = 0; c2 < 4; c2++) {
                    for(int c3 = 0; c3 < 4; c3++)
                        if(c != c3)
                            dp[i + 1][c2] = (dp[i + 1][c2] + b[c][c2][c3]) % MODN;
                }
                for(int c2 = 0; c2 < 4; c2++) {
                    nb[c2][c][c] = dp[i][c2];
                    for(int c3 = 0; c3 < 4; c3++)
                        for(int c4 = 0; c4 < 4; c4++)
                            if(c4 != c)
                                nb[c2][c3][c] = (nb[c2][c3][c] + b[c2][c3][c4]) % MODN;
                }
            }
        }
        b = nb;
    }
    cout << (dp[n][0] + dp[n][1] + dp[n][2] + dp[n][3]) % MODN << endl;
}