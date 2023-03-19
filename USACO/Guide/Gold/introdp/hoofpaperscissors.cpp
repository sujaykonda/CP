#include <bits/stdc++.h>
using namespace std;

int N, K;
int dp[100000][21][3];

int main()
{
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        char c;
        cin >> c;
        int v = c == 'H' ? 0 : (c == 'P' ? 1 : 2);
        for (int j = 0; j <= K; j++)
            dp[i][j][v] = 1;
    }

    for (int i = 1; i < N; i++)
        for (int k = 0; k < 3; k++)
            dp[i][0][k] += dp[i - 1][0][k];
    for (int j = 1; j <= K; j++)
    {
        for (int i = 1; i < N; i++)
        {
            for (int k = 0; k < 3; k++)
            {
                int best = dp[i - 1][j][k];
                best = max(best, dp[i][j - 1][0]);
                best = max(best, dp[i][j - 1][1]);
                best = max(best, dp[i][j - 1][2]);
                dp[i][j][k] += best;
            }
        }
    }
    int best = 0;
    for (int k = 0; k < 3; k++)
        best = max(best, dp[N - 1][K][k]);
    cout << best << endl;
}