#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> c(N);
    for (int i = 0; i < N; i++)
        cin >> c[i];
    vector<vector<int>> dp(N, vector<int>(N, N));
    for (int i = 0; i < N; i++)
        dp[i][i] = 1;
    for (int s = 1; s < N; s++)
    {
        for (int i = 0; i + s < N; i++)
        {
            for (int j = i; j < i + s; j++)
            {
                if (c[i] == c[i + s])
                    dp[i][i + s] = min(dp[i][i + s], dp[i][j] + dp[j + 1][i + s] - 1);
                dp[i][i + s] = min(dp[i][i + s], dp[i][j] + dp[j + 1][i + s]);
            }
        }
    }
    cout << dp[0][N - 1] << endl;
}