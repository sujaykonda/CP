#include <bits/stdc++.h>
using namespace std;

int n, m;
set<int> nonadj[200001];
set<int> unvisited;
int comp[200001];

void dfs(int s, int c)
{
    unvisited.erase(s);
    comp[s] = c;
    for (auto it = unvisited.begin(); it != unvisited.end();)
    {
        if (nonadj[s].count(*it))
        {
            it++;
            continue;
        }
        int p = *it;
        dfs(p, c);
        it = unvisited.upper_bound(p);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        nonadj[a].insert(b);
        nonadj[b].insert(a);
    }

    for (int i = 1; i <= n; i++)
        unvisited.insert(i);

    int c = 1;
    for (auto it = unvisited.begin(); it != unvisited.end();)
    {
        int p = *it;
        dfs(p, c);
        it = unvisited.upper_bound(p);
        c++;
    }

    vector<int> compsizes(c);
    for (int i = 1; i <= n; i++)
        compsizes[comp[i]]++;
    sort(compsizes.begin(), compsizes.end());
    cout << c - 1 << endl;
    for (int i = 1; i < c; i++)
        cout << compsizes[i] << " ";
    cout << endl;
}
