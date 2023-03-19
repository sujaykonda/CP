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
    freopen("superbull.in", "r", stdin);
    freopen("superbull.out", "w", stdout);
    int N;
    cin >> N;
    vector<int> t(N);
    DSU dsu(N);
    for (int i = 0; i < N; i++)
        cin >> t[i];
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            edges.push_back({t[i] ^ t[j], {i, j}});
    sort(edges.begin(), edges.end());
    long long a = 0;
    for (int i = edges.size() - 1; i >= 0; i--)
        if (dsu.unite(edges[i].s.f, edges[i].s.s))
            a += edges[i].f;
    cout << a << endl;
}