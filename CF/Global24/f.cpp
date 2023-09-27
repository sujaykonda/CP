#include <cplib/general.h>
using namespace std;
struct DSU
{
    std::vector<int> e;
    DSU(int N) : e(N, -1) { }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    int size(int x) { return -e[get(x)]; }
    bool unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return false;
        if (e[x] > e[y])
            std::swap(x, y);
        e[x] -= (e[x] == e[y]), e[y] = x;
        return true;
    }
};

int main() {
    int n; rd(n);
    vector<vector<ll>> f(n, vector<ll>(n));
    vector<pair<ll, pair<int, int>>> e;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) rd(f[i][j]);
        for(int j = 0; j < i; j++) e.pb({-f[i][j], {i, j}});
    }
    sort(e.begin(), e.end());
    DSU dsu(n);
    for(auto [u, v] : e) {
        auto [x, y] = v;
        if(dsu.unite(x, y)) {
            cout << x + 1 << " " << y + 1 << " " << ((f[x][x] + f[y][y] + 2 * u) / n) << '\n';
        }
    }

}