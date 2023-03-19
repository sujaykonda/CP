#include <bits/stdc++.h>
using namespace std;
#define modn 1000000007
int n, x;
vector<int> coins;
int dp[101][1000001];
int main()
{
    cin >> n >> x;
    coins.resize(n);
    for (int i = 0; i < n; i++)
        cin >> coins[i];
    dp[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= x; j++)
        {
            dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % modn;
            if (j + coins[i] <= x)
                dp[i][j + coins[i]] = (dp[i][j + coins[i]] + dp[i][j]) % modn;
        }
    }
    cout << dp[n][x] << endl;
}