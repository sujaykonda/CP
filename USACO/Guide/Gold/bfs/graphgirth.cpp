#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> adj[2501];
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int cycle = n + 1;
    for (int st = 1; st <= n; st++)
    {
        vector<int> d(n + 1, -1);
        queue<pair<int, int>> q;
        d[st] = 0;
        q.push({0, st});
        while (!q.empty())
        {
            int e = q.front().first, s = q.front().second;
            q.pop();
            for (int u : adj[s])
            {
                if (u == e)
                    continue;
                if (d[u] >= 0)
                    cycle = min(cycle, d[s] + d[u] + 1);
                else
                {
                    d[u] = d[s] + 1;
                    q.push({s, u});
                }
            }
        }
    }
    if (cycle == n + 1)
        cycle = -1;
    cout << cycle << endl;
}