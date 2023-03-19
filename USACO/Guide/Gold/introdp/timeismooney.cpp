#include <bits/stdc++.h>
using namespace std;

vector<int> adj[1001];
int N, M, C;
int value[1001];
int dp[1001][1001];
int main()
{
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    cin >> N >> M >> C;
    for (int i = 1; i <= N; i++)
        cin >> value[i];
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    dp[1][0] = 1;
    for (int t = 1; t <= 1000; t++)
        for (int i = 1; i <= N; i++)
            if (dp[i][t - 1] != 0)
                for (int u : adj[i])
                    dp[u][t] = max(dp[u][t], value[u] + dp[i][t - 1]);

    int best = 0;
    for (int t = 0; t <= 1000; t++)
        best = max(best, dp[1][t] - 1 - C * t * t);
    cout << best << endl;
}