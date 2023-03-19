#include <bits/stdc++.h>
using namespace std;

int N, M, K;
vector<int> combo;
int cpre[26][1000001];
int cmat[26][26];
int dp[26][1000001];

int main()
{
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);
    cin >> N >> M >> K;
    string ln;
    cin >> ln;
    combo.resize(N);
    for (int i = 0; i < N; i++)
        combo[i] = ln[i] - 'a';

    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            cin >> cmat[i][j];

    for (int k = 0; k < M; k++)
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                cmat[i][j] = min(cmat[i][j], cmat[i][k] + cmat[k][j]);

    for (int c = 0; c < M; c++)
        for (int i = 1; i <= N; i++)
            cpre[c][i] = cpre[c][i - 1] + cmat[combo[i - 1]][c];

    for (int c = 0; c < M; c++)
        for (int i = 1; i < 2 * K; i++)
            dp[c][i] = cpre[c][i];

    for (int i = 2 * K; i <= N; i++)
    {
        for (int c = 0; c < M; c++)
        {
            dp[c][i] = dp[c][i - 1] + cpre[c][i] - cpre[c][i - 1];
            for (int c2 = 0; c2 < M; c2++)
                dp[c][i] = min(dp[c][i], dp[c2][i - K] + cpre[c][i] - cpre[c][i - K]);
        }
    }
    int best = dp[0][N];
    for (int c = 1; c < M; c++)
        best = min(best, dp[c][N]);
    cout << best << endl;
}