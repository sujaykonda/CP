#include <bits/stdc++.h>
using namespace std;
int N, K;
long long grid[800][800];
long long P[800][800];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("lazy.in", "r", stdin);
    freopen("lazy.out", "w", stdout);
    cin >> N >> K;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> grid[N + i - j - 1][i + j];

    for (int i = 1; i <= 2 * N - 1; i++)
    {
        for (int j = 1; j <= 2 * N - 1; j++)
        {
            P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + grid[i - 1][j - 1];
        }
    }
    long long m = 0;
    for (int i = 0; i <= 2 * N - 2 * K - 2; i++)
    {
        for (int j = 0; j <= 2 * N - 2 * K - 2; j++)
        {
            if ((i + j) % 2 == N % 2)
                continue;
            m = max(m, P[i + 2 * K + 1][j + 2 * K + 1] - P[i + 2 * K + 1][j] - P[i][j + 2 * K + 1] + P[i][j]);
        }
    }
    if (K >= 2 * N)
    {
        m = P[2 * N - 1][2 * N - 1];
    }
    cout << m << endl;
}