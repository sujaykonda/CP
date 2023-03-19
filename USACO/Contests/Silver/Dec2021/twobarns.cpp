#include <bits/stdc++.h>

using namespace std;

void dfs(int i, vector<vector<int>> *adj, vector<bool> *done, vector<int> *path)
{
    if ((*done)[i])
        return;

    (*done)[i] = true;
    path->push_back(i);

    for (int neighbor : (*adj)[i])
        dfs(neighbor, adj, done, path);
}

int T;
int main()
{
    // freopen("in.in", "r", stdin);
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N, M;
        vector<vector<int>> adj;
        vector<bool> done;
        vector<int> spath;
        vector<int> epath;
        vector<vector<int>> paths;
        cin >> N;
        cin >> M;

        adj.resize(N + 1);
        done.resize(N + 1);
        for (int c = 0; c < M; c++)
        {
            int i, j;
            cin >> i >> j;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }

        dfs(1, &adj, &done, &spath);
        sort(spath.begin(), spath.end());
        dfs(N, &adj, &done, &epath);
        sort(epath.begin(), epath.end());

        for (int i = 2; i <= N - 1; i++)
        {
            if (!done[i])
            {
                vector<int> path;
                dfs(i, &adj, &done, &path);
                paths.push_back(path);
            }
        }

        if (epath.size() == 0)
        {
            cout << 0 << endl;
            continue;
        }

        long long mincost = INT_MAX;
        for (int p : spath)
        {
            long long plen = (*lower_bound(epath.begin(), epath.end(), p)) - p;
            long long len1 = plen / 2;
            long long len2 = plen - plen / 2;
            mincost = len1 * len1 + len2 * len2;
        }
        for (int i = 0; i < paths.size(); i++)
        {
            long long min1 = N;
            long long min2 = N;
            for (long long p : paths[i])
            {
                int si = lower_bound(spath.begin(), spath.end(), p) - spath.begin();
                int ei = lower_bound(epath.begin(), epath.end(), p) - epath.begin();
                if (si < spath.size())
                    min1 = min(min1, abs(spath[si] - p));
                if (si > 0)
                    min1 = min(min1, abs(spath[si - 1] - p));
                if (ei < epath.size())
                    min2 = min(min2, abs(epath[ei] - p));
                if (ei > 0)
                    min2 = min(min2, abs(epath[ei - 1] - p));
            }
            mincost = min(mincost, min1 * min1 + min2 * min2);
        }
        cout << mincost << endl;
    }
}