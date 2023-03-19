#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
struct DSU
{
    vector<int> e;
    DSU(int N) { e = vector<int>(N, -1); }
    int get(int x) { return e[x] < 0 ? x : x = get(e[x]); }
    int size(int x) { return -e[x]; }
    bool unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return false;
        if (e[x] > e[y])
            swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};

int main()
{
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
    int A, B, n, m;
    cin >> A >> B >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    a.push_back(0);
    a.push_back(A);
    vector<int> b(m);
    for (int i = 0; i < m; i++)
        cin >> b[i];
    b.push_back(0);
    b.push_back(B);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < m; j++)
            edges.push_back({a[i + 1] - a[i], {(m + 1) * i + j, (m + 1) * i + j + 1}});
    for (int j = 0; j <= m; j++)
        for (int i = 0; i < n; i++)
            edges.push_back({b[j + 1] - b[j], {(m + 1) * i + j, (m + 1) * (i + 1) + j}});
    sort(edges.begin(), edges.end());
    DSU dsu((n + 1) * (m + 1));
    long long ans = 0;
    for (pair<int, pair<int, int>> &edge : edges)
        if (dsu.unite(edge.s.f, edge.s.s))
            ans += edge.f;
    cout << ans << endl;
}