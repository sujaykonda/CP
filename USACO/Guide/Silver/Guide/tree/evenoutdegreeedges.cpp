#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001

vector<int> adj[MAXN];
vector<int> tadj[MAXN];

bool done[MAXN];

void dfs(int s)
{
    done[s] = true;
    for (int u : adj[s])
    {
        if (!done[u])
        {
            tadj[s].push_back(u);
            tadj[u].push_back(s);
            dfs(u);
        }
    }
}