#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

int main()
{
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    int N, xl, yl, xb, yb;
    cin >> N >> xl >> yl >> xb >> yb;
    yl += 1000000000;
    yb += 1000000000;

    pair<int, int> c;
    map<int, vector<int>> adj;
    for (int i = 0; i < N; i++)
    {
        cin >> c.f >> c.s;
        c.s += 1000000000;
        adj[c.f].push_back(c.s);
        adj[c.s].push_back(c.f);
    }

    set<int> done;
    queue<pair<int, int>> q;
    q.push({xl, 0});
    q.push({yl, 0});
    int s, d;
    while (!q.empty())
    {
        s = q.front().f, d = q.front().s;
        if (s == xb || s == yb)
            break;
        q.pop();
        done.insert(s);
        for (int u : adj[s])
            if (!done.count(u))
                q.push({u, d + 1});
    }
    if (q.empty())
        cout << -1 << endl;
    else
        cout << d << endl;
}