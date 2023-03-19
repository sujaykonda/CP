#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> adj[3001];
int done[3001];

void dfs(int s, int id)
{
    if (done[s] == id || done[s] == -1)
        return;
    done[s] = id;
    for (int u : adj[s])
        dfs(u, id);
}

int main()
{
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= N; i++)
    {
        int c;
        cin >> c;
        int s = 1;
        while (done[s] == -1)
            s++;
        dfs(s, i);
        bool good = true;
        for (int j = 1; j <= N; j++)
        {
            // cout << done[j] << " ";
            good = done[j] == -1 || done[j] == i;
            if (!good)
                break;
        }
        if (good)
            cout << "YES\n";
        else
            cout << "NO\n";
        done[c] = -1;
    }
}