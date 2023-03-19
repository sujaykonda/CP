#include <bits/stdc++.h>
using namespace std;
#define getbit(mask, i) (mask & (1 << i)) > 0
int main()
{
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    for (int i = 0; i < n; i++)
        cin >> w[i];

    vector<pair<int, int>> dp(1 << n, {n, x});
    dp[0] = {0, 0};
    for (int i = 1; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (getbit(i, j))
            {
                if ((dp[i ^ (1 << j)].second + w[j]) > x)
                    dp[i] = min(dp[i], {dp[i ^ (1 << j)].first + 1, w[j]});
                else
                    dp[i] = min(dp[i], {dp[i ^ (1 << j)].first, dp[i ^ (1 << j)].second + w[j]});
            }
        }
    }
    cout << dp[(1 << n) - 1].first + 1 << endl;
}