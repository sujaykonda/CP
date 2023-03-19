#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
int depth[200001];
vector<int> adj[200001];
vector<int> trav;

int length[200001];

void dfs(int s, int e)
{
    depth[s] = depth[e] + 1;
    trav.push_back(s);
    for (int u : adj[s])
    {
        if (u == e)
            continue;
        dfs(u, s);
        trav.push_back(s);
    }
}

void solve()
{
    vector<int> bd(2 * n);
    for (int i = 2 * n - 2; i >= 0; i--)
        bd[i] = max(bd[i + 1], depth[trav[i]]);
    priority_queue<pair<int, int>> bestlcas;
    for (int i = 0; i < trav.size(); i++)
        bestlcas.push({bd[i] - 2 * depth[trav[i]], i});

    for (int i = 0; i < trav.size(); i++)
    {
        while (bestlcas.top().second < i)
            bestlcas.pop();
        length[trav[i]] = max(length[trav[i]], depth[trav[i]] + bestlcas.top().first);
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    solve();
    reverse(trav.begin(), trav.end());
    solve();
    for (int i = 1; i <= n; i++)
        cout << length[i] << " ";
    cout << endl;
}