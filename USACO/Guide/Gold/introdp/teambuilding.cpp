#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define modn 1000000009

int N, M, K;

vector<int> FJ;
vector<int> FP;
ll dp[1001][1001][11];

int main()
{
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    cin >> N >> M >> K;
    FJ.resize(N);
    FP.resize(M);
    for (int i = 0; i < N; i++)
        cin >> FJ[i];
    for (int i = 0; i < M; i++)
        cin >> FP[i];
    sort(FJ.rbegin(), FJ.rend());
    sort(FP.rbegin(), FP.rend());

    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++)
            dp[i][j][0] = 1;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            for (int k = 1; k <= K; k++)
            {
                dp[i][j][k] = dp[i - 1][j][k] + dp[i][j - 1][k] - dp[i - 1][j - 1][k];
                if (FJ[i - 1] > FP[j - 1])
                    dp[i][j][k] += dp[i - 1][j - 1][k - 1];
                dp[i][j][k] += modn;
                dp[i][j][k] %= modn;
            }
        }
    }
    cout << dp[N][M][K] << endl;
}