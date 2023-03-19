#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, q;
vector<int> adj[200001];
vector<int> path;
int ac[200001][20];

int jmp(int x, int k)
{
    if (k == 0)
        return x;

    int log2 = 0, p = 1;
    while (2 * p <= k)
        p *= 2, log2++;
    return jmp(ac[x][log2], k - p);
}

void build(int s, int e)
{
    path.push_back(s);
    int log2 = 0;
    int p = 1;
    while (p < path.size())
        ac[s][log2] = path[path.size() - p - 1], log2++, p *= 2;
    for (int u : adj[s])
    {
        if (u == e)
            continue;
        build(u, s);
    }
    path.pop_back();
}

int main()
{
    cin >> n >> q;
    for (int i = 2; i <= n; i++)
    {
        int b;
        cin >> b;
        adj[i].push_back(b);
        adj[b].push_back(i);
    }
    vector<int> path;
    build(1, 0);
    while (q--)
    {
        int x, k;
        cin >> x >> k;
        int r = jmp(x, k);
        if (r == 0)
            cout << "-1" << endl;
        else
            cout << r << endl;
    }
}