#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> d;
vector<int> dp;
void dfs(int s)
{
    if (dp[s] != -1)
        return;
    dp[s] = d[s];
    for (int u : adj[s])
    {
        if (d[s] < d[u])
        {
            dfs(u);
            dp[s] = min(dp[s], dp[u]);
        }
        else
            dp[s] = min(dp[s], d[u]);
    }
}

void testcase()
{
    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 1; i <= n; i++)
        adj[i].clear();
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    d.resize(n + 1);
    fill(d.begin(), d.end(), -1);
    queue<int> q;
    d[1] = 0;
    q.push(1);
    while (!q.empty())
    {
        int s = q.front();
        q.pop();
        for (int u : adj[s])
        {
            if (d[u] == -1)
            {
                d[u] = d[s] + 1;
                q.push(u);
            }
        }
    }

    dp.resize(n + 1);
    fill(dp.begin(), dp.end(), -1);
    for (int i = 1; i <= n; i++)
    {
        dfs(i);
        cout << dp[i] << " ";
    }
    cout << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
        testcase();
}