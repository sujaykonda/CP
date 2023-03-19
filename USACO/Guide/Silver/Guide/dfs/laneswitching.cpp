#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N, M, R;

int L, S, P;
vector<int> lanes[101];
vector<pair<int, int>> adj[100000];
int done[100000];

int intersection(int s1, int e1, int s2, int e2)
{
    if (e2 <= s1)
        return -1;
    if (e1 <= s2)
        return -1;
    return min(e1, e2) - max(s1, s2);
}

bool dfs(int s, int l)
{
    if (done[s])
        return INT_MAX;
    bool works = false;
    for (pair<int, int> u : adj[s])
    {
        if (u.second < l)
            continue;
        works = works || dfs(u.first, l);
    }
    return works;
}

int main()
{
    cin >> N >> M >> R;
    cin >> L >> S >> P;

    for (int i = 0; i < M - 1; i++)
    {
        int l, s, p;
        cin >> l >> s >> p;
        lanes[l].push_back(p);
        lanes[l].push_back(p + s);
    }

    for (int l = 0; l < N; l++)
    {
        lanes[l].push_back(0);
        lanes[l].push_back(R);
        sort(lanes[l].begin(), lanes[l].end());
    }

    int v = 0;
    for (int l = 0; l < N - 1; l++)
    {
        int nv = v + lanes[l].size() / 2;
        int j = 0;
        for (int i = 0; i < lanes[l].size(); i += 2)
        {
            while (j < lanes[l + 1].size() && intersection(lanes[l][i], lanes[l][i + 1], lanes[l + 1][j], lanes[l + 1][j + 1]) < 0)
                j += 2;
            while (j < lanes[l + 1].size() && intersection(lanes[l][i], lanes[l][i + 1], lanes[l + 1][j], lanes[l + 1][j + 1]) >= 0)
            {
                int val = intersection(lanes[l][i], lanes[l][i + 1], lanes[l + 1][j], lanes[l + 1][j + 1]) - S;
                adj[v + i / 2].push_back({nv + j / 2, val});
                j += 2;
            }
            j = max(0, j - 2);
        }
        v = nv;
    }
    for (int i = 0; i < lanes[N - 1].size(); i += 2)
    {
        done[v + i / 2] = 1;
    }
    int s = -1;
    for (int i = 0; i < lanes[L].size(); i += 2)
        if (lanes[L][i] <= P && lanes[L][i + 1] >= P + S)
            s = i / 2;
    if (s == -1)
    {
        cout << "Impossible" << endl;
        return 0;
    }
    int lo = 0, hi = R;
    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (dfs(s, mid))
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    if (hi < 0)
        cout << "Impossible" << endl;
    else
        cout << (double)hi / 2 << endl;
}