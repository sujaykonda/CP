#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<int> adj[200001];

int depth[200001];

int timer = 0;
int tin[200001];
int euler_tour[400001];

int sparse[400001][20];

void dfs(int s, int e)
{
    depth[s] = depth[e] + 1;
    tin[s] = timer;
    euler_tour[timer++] = s;

    for (int u : adj[s])
    {
        if (u == e)
            continue;
        dfs(u, s);
        euler_tour[timer++] = s;
    }
}

void build()
{
    for (int i = 0; i < timer; i++)
        sparse[i][0] = depth[euler_tour[i]];
    int log2 = 1, p = 2;
    while (p < n)
    {
        for (int i = 0; i <= timer - p; i++)
            sparse[i][log2] = min(sparse[i][log2 - 1], sparse[i + p / 2][log2 - 1]);
        log2++, p *= 2;
    }
}

int main()
{
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    timer = 0;
    dfs(1, 0);
    build();
    for (int qi = 0; qi < q; qi++)
    {
        int x, y;
        cin >> x >> y;
        int a = tin[x], b = tin[y];
        int md = n;
        while (a < b)
        {
            int log2 = 0, p = 1;
            while (a + 2 * p <= b)
                p *= 2, log2++;
            md = min(md, sparse[a][log2]);
            a += p;
        }
        cout << depth[x] + depth[y] - 2 * md << endl;
    }
}