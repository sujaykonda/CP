#include <bits/stdc++.h>
using namespace std;
#define modn 1000000007
#define maxn 20
#define max2n 1 << maxn
vector<int> adj[maxn];
int dp[maxn][max2n];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[--a].push_back(--b);
    }
    dp[0][1] = 1;
    for (int j = 1; j < (1 << n); j++)
        for (int i = 0; i < n; i++)
            if (dp[i][j] > 0)
                for (int u : adj[i])
                    if ((j & (1 << u)) == 0)
                        dp[u][j + (1 << u)] = (dp[u][j + (1 << u)] + dp[i][j]) % modn;
    cout << dp[n - 1][(1 << n) - 1] << endl;
}