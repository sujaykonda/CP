#include <bits/stdc++.h>
using namespace std;

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
struct Edge
{
    int a, b;
    long long c;
    Edge(int _a, int _b, long long _c) { a = _a, b = _b, c = _c; }
};
bool operator<(const Edge &e, const Edge &e2) { return e.c < e2.c; }

vector<pair<int, int>> cows;
long long calc(int i, int j) { return pow((long long)(cows[i].first - cows[j].first), 2) +
                                      pow((long long)(cows[i].second - cows[j].second), 2); }

int main()
{
    int N;
    cin >> N;
    cows.resize(N);
    for (int i = 0; i < N; i++)
        cin >> cows[i].first >> cows[i].second;
    sort(cows.begin(), cows.end());
    vector<Edge> edges;
    for (int i = 0; i < N; i++)
        for (int j = max(0, i - 20); j < N && j <= i + 20; j++)
            edges.push_back(Edge(i, j, calc(i, j)));
    sort(edges.begin(), edges.end());
    DSU dsu(N);
    long long sum = 0;
    for (Edge edge : edges)
        if (dsu.unite(edge.a, edge.b))
            sum += edge.c;
    cout << sum << endl;
}