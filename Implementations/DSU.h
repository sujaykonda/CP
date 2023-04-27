#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU
{
    vector<int> e;
    DSU(int N) : e(N, -1) { }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    int size(int x) { return -e[get(x)]; }
    int unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return x;
        if (e[x] > e[y])
            swap(x, y);
        e[x] += e[y], e[y] = x;
        return x;
    }
};
