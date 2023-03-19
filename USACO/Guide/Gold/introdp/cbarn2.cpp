#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll N, K;
vector<ll> r;

ll dp[101][201][8];

int main()
{
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);
    cin >> N >> K;
    r.resize(2 * N);
    for (int i = 0; i < N; i++)
        cin >> r[i], r[i + N] = r[i];

    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < i + N; j++)
            dp[i][j][1] = dp[i][j - 1][1] + r[j] * (j - i);

    for (int k = 2; k <= K; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < i + N; j++)
            {
                dp[i][j][k] = dp[i][j][k - 1];
                for (int d = j - 1; d > i; d--)
                {
                    dp[i][j][k] = min(dp[i][j][k], dp[i][d][k - 1] + dp[(d + 1) % N][(d + 1) % N + (j - d - 1)][1]);
                }
            }
        }
    }
    ll best = dp[0][N - 1][K];
    for (int i = 1; i < N; i++)
        best = min(best, dp[i][i + N - 1][K]);
    cout << best << endl;
}