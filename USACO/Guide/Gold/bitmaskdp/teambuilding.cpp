#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, p, k;
    cin >> n >> p >> k;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].first, a[i].second = i;
    sort(a.begin(), a.end(), greater<pair<int, int>>());

    // save the sorted order so we can input the s array in order
    vector<int> so(n);
    for (int i = 0; i < n; i++)
        so[a[i].second] = i;

    vector<vector<int>> s(n, vector<int>(p));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            cin >> s[so[i]][j];

    vector<vector<long long>> dp((1 << p), vector<long long>(n + 1, -1));
    dp[0][0] = 0;
    for (int j = 1; j <= n; j++)
        for (int i = 0; i < (1 << p); i++)
        {
            int c = j - bitset<7>(i).count() - 1;
            dp[i][j] = dp[i][j - 1];
            dp[i][j] += (dp[i][j] != -1 && c < k) * a[j - 1].first;
            for (int m = 0; m < p; m++)
                if ((i & (1 << m)) > 0 && dp[i ^ (1 << m)][j - 1] != -1)
                    dp[i][j] = max(dp[i][j], s[j - 1][m] + dp[i ^ (1 << m)][j - 1]);
        }
    cout << dp[(1 << p) - 1][n] << endl;
}