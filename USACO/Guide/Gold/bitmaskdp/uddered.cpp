#include <bits/stdc++.h>
using namespace std;
#define inf 100000
int main()
{
    string heard;
    cin >> heard;
    vector<int> letters(26, -1);
    int n = 0;
    for (int i = 0; i < heard.length(); i++)
        if (letters[heard[i] - 'a'] == -1)
            letters[heard[i] - 'a'] = n++;
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < heard.length() - 1; i++)
        adj[letters[heard[i] - 'a']][letters[heard[i + 1] - 'a']]++;

    vector<int> dp(1 << n, inf);
    dp[0] = 1;
    for (int i = 1; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i & (1 << j)) > 0)
            {
                int ndp = dp[i ^ (1 << j)];
                for (int k = 0; k < n; k++)
                {
                    if ((i & (1 << k)) > 0)
                    {
                        ndp += adj[j][k];
                    }
                }
                dp[i] = min(dp[i], ndp);
                // cout << bitset<10>(i) << " " << dp[i] << endl;
            }
        }
    }
    cout << dp[(1 << n) - 1] << endl;
}