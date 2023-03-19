#include <bits/stdc++.h>
using namespace std;

long long N;
long long target = 0;
long long haybales[200001];
long long value[200001];
vector<long long> adj[200001];
vector<tuple<long long, long long, long long>> cmd;

void calcVal(long long s, long long e)
{
    value[s] = haybales[s] - target;
    for (long long u : adj[s])
    {
        if (u == e)
            continue;

        calcVal(u, s);
        value[s] += value[u];
    }
}

bool byValue(long long i, long long j) { return value[i] > value[j]; }

void dfs(long long s, long long e)
{
    sort(adj[s].begin(), adj[s].end(), byValue);
    for (long long u : adj[s])
    {
        if (u == e)
            continue;
        if (haybales[u] > value[u])
        {
            if (value[u] > 0)
                cmd.push_back({u, s, value[u]});
            else if (value[u] < 0)
                cmd.push_back({s, u, -value[u]});
            dfs(u, s);
        }
        else
        {
            dfs(u, s);
            if (value[u] > 0)
                cmd.push_back({u, s, value[u]});
            else if (value[u] < 0)
                cmd.push_back({s, u, -value[u]});
        }
    }
}

int main()
{
    cin >> N;
    for (long long i = 1; i <= N; i++)
    {
        cin >> haybales[i];
        target += haybales[i];
    }
    target /= N;

    for (long long i = 0; i < N - 1; i++)
    {
        long long u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    calcVal(1, 0);
    dfs(1, 0);
    cout << cmd.size() << endl;
    for (long long i = 0; i < cmd.size(); i++)
        cout << get<0>(cmd[i]) << " " << get<1>(cmd[i]) << " " << get<2>(cmd[i]) << endl;
}