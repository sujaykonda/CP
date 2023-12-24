#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
struct BIT {
    std::vector<ll> tree;
    BIT(int n) { tree = std::vector<ll>(n + 1); }
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


int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int T; cin >> T;
    while(T--) {
        int F, B; cin >> F >> B;
        int N, M, S, E; cin >> N >> M >> S >> E;
        S--, E--;
        vector<int> R(F);
        for(int i = 0; i < F; i++) cin >> R[i], R[i]--;
        vector<vector<int>> adj(N);
        for(int i = 0; i < M; i++) {
            int a, b; cin >> a >> b;
            a--, b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        auto bfs = [&] (int st) {
            vector<int> d(N, -1);
            d[st] = 0;
            queue<int> q; q.push(st);
            while(!q.empty()) {
                int s = q.front(); q.pop();
                for(int u : adj[s]) {
                    if(d[u] == -1) {
                        d[u] = d[s] + 1;
                        q.push(u);
                    }
                }
            }
            return d;
        };
        vector<int> dS = bfs(S);
        vector<int> dE = bfs(E);
        int se = dS[E];
        vector<pair<int, int>> p;
        for(int i = 0; i < F; i++) {
            p.push_back({dS[R[i]] + dE[R[i]] - se, i});
        }
        sort(p.begin(), p.end());
        vector<int> rev(F);
        for(int i = 0; i < p.size(); i++) rev[p[i].second] = i;
        int best = 0;
        BIT sm(F), cnt(F);
        for(int i = 0; i < F; i++) {
            if(B < (i + 1) * se) break;
            sm.add(rev[i] + 1, p[rev[i]].first);
            cnt.add(rev[i] + 1, 1);
            best = max(best, (int)cnt.sum(sm.lb(B - (i + 1) * se)));
        }
        cout << best << endl;
    }
}