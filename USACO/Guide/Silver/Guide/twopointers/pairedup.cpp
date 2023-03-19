// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
int N;
vector<pair<int, int>> c;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("pairup.in", "r", stdin);
    freopen("pairup.out", "w", stdout);
    cin >> N;
    c.resize(N);
    for (int i = 0; i < N; i++)
        cin >> c[i].second >> c[i].first;
    sort(c.begin(), c.end());
    int i = 0, j = N - 1;
    int m = 0;
    while (i != j)
    {
        if (c[i].second == 0)
            i++;
        if (c[j].second == 0)
            j--;
        int change = min(c[i].second, c[j].second);
        c[i].second -= change;
        c[j].second -= change;
        m = max(c[i].first + c[j].first, m);
    }
    cout << m << endl;
}
