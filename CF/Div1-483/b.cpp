#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];

    vector<vector<int>> pyr(n);
    pyr[0] = a;
    for(int i = 1; i < n; i++) {
        pyr[i].resize(pyr[i - 1].size() - 1);
        for(int j = 0; j < pyr[i].size(); j++)
            pyr[i][j] = pyr[i - 1][j] ^ pyr[i - 1][j + 1];
    }

    vector<vector<int>> dp(n, vector<int>(n));
    for(int s = 0; s < n; s++) {
        for(int i = 0; i < n - s; i++) {
            dp[i][i + s] = pyr[s][i];
            if(i + s > 0)
                dp[i][i + s] = max(dp[i][i + s], dp[i][i + s - 1]);
            if(i < n - 1)
                dp[i][i + s] = max(dp[i][i + s], dp[i + 1][i + s]);
        }
    }
    int q;
    cin >> q;
    for(int qi = 0; qi < q; qi++) {
        int a, b;
        cin >> a >> b;
        cout << dp[a - 1][b - 1] << endl;
    }
}