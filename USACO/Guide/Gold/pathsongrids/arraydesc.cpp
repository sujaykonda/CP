#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define modn 1000000007
ll dp[100000][102];

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> x(n);
    for (int i = 0; i < n; i++)
        cin >> x[i];
    if (x[0] == 0)
        for (int j = 1; j <= m; j++)
            dp[0][j] = 1;
    else
        dp[0][x[0]] = 1;
    for (int i = 1; i < n; i++)
    {
        if (x[i] == 0)
            for (int j = 1; j <= m; j++)
                for (int j2 = max(j - 1, 1); j2 <= min(j + 1, m); j2++)
                    dp[i][j2] = (dp[i][j2] + dp[i - 1][j]) % modn;
        else
            for (int j = max(x[i] - 1, 1); j <= min(x[i] + 1, m); j++)
                dp[i][x[i]] = (dp[i][x[i]] + dp[i - 1][j]) % modn;
    }
    ll s = 0;
    for (int j = 1; j <= m; j++)
        s = (s + dp[n - 1][j]) % modn;
    cout << s << endl;
}