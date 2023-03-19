#include <bits/stdc++.h>
using namespace std;
#define MAXN 5001
#define inf 10001
int dp[MAXN][MAXN];
int main()
{
    string a, b;
    cin >> a >> b;
    int n = a.length(), m = b.length();
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int i = 0; i <= m; i++)
        dp[0][i] = i;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = inf;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            dp[i][j] = min(dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]), min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
    cout << dp[n][m] << endl;
}