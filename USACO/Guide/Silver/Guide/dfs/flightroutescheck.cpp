#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> adj[100001];
vector<int> radj[100001];
bool done[100001];
bool rdone[100001];

void dfs(int s)
{
    done[s] = true;
    for (int u : adj[s])
        if (!done[u])
            dfs(u);
}

void rdfs(int s)
{
    rdone[s] = true;
    for (int u : radj[s])
        if (!rdone[u])
            rdfs(u);
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }
    dfs(1);
    rdfs(1);
    for (int i = 1; i <= n; i++)
    {
        if (!done[i])
        {
            cout << "NO\n"
                 << 1 << " " << i << "\n";
            return 0;
        }
        if (!rdone[i])
        {
            cout << "NO\n"
                 << i << " " << 1 << "\n";
            return 0;
        }
    }
    cout << "YES\n";
}