#include <bits/stdc++.h>
using namespace std;

int N, Q;
vector<pair<int, int>> adj[1000001];
bitset<1000001> done;
bitset<1000001> color;

bool dfs(pair<int, int> &cc, int s)
{
    done[s] = 1;
    for (auto &[u, v] : adj[s])
    {
        if (!done[u])
        {
            color[u] = v ^ color[s];
            if (color[u])
                cc.first++;
            else
                cc.second++;
            if (!dfs(cc, u))
                return false;
        }
        else
        {
            if (color[u] ^ v == !color[s])
                return false;
        }
    }
    return true;
}

int main()
{
    int s = 0;
    int T;
    cin >> T;
    while (T--)
    {
        cin >> N >> Q;
        for (int i = 0; i < Q; i++)
        {
            int t, x, y;
            cin >> t >> x >> y;
            x += s, y += s, t--;
            adj[x].push_back({y, !t});
            adj[y].push_back({x, !t});
        }
        bool consistent = true;
        int mx = 0;
        for (int i = s + 1; i <= s + N; i++)
        {
            if (!done[i])
            {
                pair<int, int> cc;
                color[i] = 1;
                cc.first++;
                if (!dfs(cc, i))
                {
                    consistent = false;
                }
                mx += max(cc.first, cc.second);
            }
        }
        if (consistent)
            cout << mx << endl;
        else
            cout << -1 << endl;
        s += N;
    }
    return 0;
}
