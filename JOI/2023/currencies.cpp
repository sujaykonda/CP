#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
    int lb(ll x) {
        ll s = 0, p = 0;
        for(int i = lg(tree.size()); i >= 0; i--)
            if(p + (1 << i) < tree.size() && s + tree[p + (1 << i)] <= x)
                p += (1 << i), s += tree[p];
        return p;
    }
};

struct Edge {
    int a, b;
    vector<int> c;
};

struct Query {
    int S, E, i;
    ll s;
};

const int BS = 450;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<Edge> edge(N - 1);
    vector<vector<int>> inc(N);
    for(int i = 0; i < N - 1; i++) {
        cin >> edge[i].a >> edge[i].b;
        edge[i].a--, edge[i].b--;
        inc[edge[i].a].push_back(i);
        inc[edge[i].b].push_back(i);
    }
    vector<pair<ll, int>> cp(M);
    for(int i = 0; i < M; i++) {
        cin >> cp[i].second >> cp[i].first;
        cp[i].second--;
    }
    sort(cp.begin(), cp.end());
    for(int i = 0; i < M; i++) {
        edge[cp[i].second].c.push_back(i);
    }
    vector<int> in(N);
    vector<int> o;
    function<void(int, int)> dfs = [&] (int s, int e) {
        in[s] = o.size();
        for(int ei : inc[s]) {
            int u = (edge[ei].a == s) ? edge[ei].b : edge[ei].a;
            if(u != e) {
                for(int c : edge[ei].c) o.push_back(c);
                dfs(u, s);
                for(int c : edge[ei].c) o.push_back(c);
            }
        }
    };
    dfs(0, -1);
    vector<Query> queries(Q);
    vector<int> gold(Q);
    for(int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b >> gold[i] >> queries[i].s;
        a--, b--;
        if(in[a] > in[b]) swap(a, b);
        queries[i].S = in[a];
        queries[i].E = in[b];
        queries[i].i = i;
    }
    sort(queries.begin(), queries.end(), [&] (Query a, Query b) {
        return (a.S / BS == b.S / BS) ? (a.E < b.E) : (a.S / BS < b.S / BS);
    });

    vector<int> ans(Q);
    vector<int> active(M);
    BIT smbit(M);
    BIT actbit(M);
    int totalact = 0;
    auto toggle = [&] (int x) {
        if(active[x]) {
            actbit.add(x + 1, -1);
            smbit.add(x + 1, -cp[x].first);
            totalact--;
        } else {
            actbit.add(x + 1, 1);
            smbit.add(x + 1, cp[x].first);
            totalact++;
        }
        active[x] ^= 1;
    };
    int L = 0, R = 0;
    for(int i = 0; i < Q; i++) {
        while(L < queries[i].S) {
            toggle(o[L++]);
        }
        while(R < queries[i].E) {
            toggle(o[R++]);
        }
        while(L > queries[i].S) {
            toggle(o[--L]);
        }
        while(R > queries[i].E) {
            toggle(o[--R]);
        }
        ans[queries[i].i] = totalact - actbit.sum(smbit.lb(queries[i].s));
    }
    for(int i = 0; i < Q; i++) {
        if(gold[i] < ans[i]) cout << -1 << '\n';
        else cout << gold[i] - ans[i] << '\n';
    }
}