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

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> adj(N + 1);
    vector<int> ecnt(N + 1);
    set<pair<int, int>> cntset;
    vector<int> order;
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        ecnt[a]++, ecnt[b]++;
    }
    for(int i = 1; i <= N; i++)
        cntset.insert({ecnt[i], i});
    while(cntset.size() > 0) {
        int i = (*cntset.begin()).second;
        cntset.erase(cntset.begin());
        ecnt[i] = -1;
        order.push_back(i);
        for(int u : adj[i]) {
            if(ecnt[u] != -1) {
                cntset.erase({ecnt[u], u});
                ecnt[u]--;
                cntset.insert({ecnt[u], u});
            }
        }
    }
    reverse(order.begin(), order.end());
    vector<bool> done(N + 1);
    DSU dsu(N + 1);
    int mx = 0;
    for(int o : order) {
        int c = 0;
        for(int u : adj[o])
            if(done[u])
                dsu.unite(o, u), c++;
        mx = max(mx, dsu.size(dsu.get(o)) * c);
        done[o] = true;
    }
    cout << mx << endl;
}