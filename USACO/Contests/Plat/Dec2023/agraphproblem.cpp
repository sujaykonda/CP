#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k] + MOD, s %= MOD, k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x + MOD, tree[k] %= MOD, k += k&-k; }
};

vector<int> e;
int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

int main() {
    int N, M; cin >> N >> M;
    vector<pair<pair<int, int>, pair<int, int>>> edges(M);
    vector<vector<int>> l(N + 1);
    for(int i = 1; i <= N; i++) l[i].push_back(i);
    e.resize(N + 1, -1);

    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        edges[i].first = {a, b};
        a = get(a), b = get(b);
        edges[i].second = {a, b};
        if(a == b) continue;
        if(e[a] > e[b]) swap(a, b);
        for(int u : l[b]) l[a].push_back(u);
        l[b].clear();
        e[a] += e[b], e[b] = a;
    }
    int rt = get(1);
    vector<int> o = l[rt];


    BIT bit(N + 1);
    vector<pair<int, int>> range(N + 1);
    for(int i = 0; i < N; i++) range[o[i]] = {i + 1, i + 2};
    vector<ll> pw(N + 1, 1);
    for(int i = 0; i < N; i++) pw[i + 1] = (700000005 * pw[i]) % MOD;
    for(int i = 0; i < M; i++) {
        auto [a, b] = edges[i].first;
        auto [pa, pb] = edges[i].second;
        if(range[pa].first > range[pb].first) swap(a, b), swap(pa, pb);
        if(range[pb].second <= range[pa].second) continue;
        ll av = (((bit.sum(range[a].first) * 700000005) % MOD + i + 1) * (pw[range[pb].second - range[pb].first - 1])) % MOD;
        ll bv = (((bit.sum(range[b].first) * 700000005) % MOD + i + 1) * (pw[range[pa].second - range[pa].first - 1])) % MOD;
        bit.add(range[pa].first, bv);
        bit.add(range[pa].second, -bv);
        bit.add(range[pb].first, av);
        bit.add(range[pb].second, -av);
        range[pa].second = range[pb].second;
    }
    ll pw2 = 1;
    for(int i = 0; i <= N - 3; i++) pw2 = (pw2 * 10) % MOD;
    for(int i = 1; i <= N; i++) cout << (bit.sum(range[i].first) * pw2) % MOD << endl;
}