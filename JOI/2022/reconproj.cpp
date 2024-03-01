#include <bits/stdc++.h>
using namespace std;

// dsu by rank
struct DSU
{
    std::vector<int> e;
    DSU(int N) : e(N, -1) { }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return false;
        if (e[x] > e[y])
            std::swap(x, y);
        e[x] -= (e[x] == e[y]);
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N, M; cin >> N >> M;
    vector<pair<int, pair<int, int>>> e(M);
    for(int i = 0; i < M; i++) cin >> e[i].second.first >> e[i].second.second >> e[i].first;

    
}