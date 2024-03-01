#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 1;
struct D {
    pair<int, int> best, best2;
    D() { best = best2 = {0, INF}; }
    friend D comb(D a, D b) {
        if(a.best.second > b.best.second) {
            if(b.best.first != a.best.first) a.best2 = a.best;
            a.best = b.best;
        } else if(a.best2.second > b.best.second) {
            if(a.best.first != b.best.first) a.best2 = b.best;
        }
        if(a.best2.second > b.best2.second) {
            if(a.best.first != b.best2.first) a.best2 = b.best2;
        }
        return a;
    }
};
struct SegT {
    int n;
    vector<D> t;
    SegT(int _n) { n = _n, t.resize(2 * n + 1); }
    void mod(int k, int c, int v) {
        t[k += n].best = {c, v}; 
        for (; k /= 2; ) t[k] = comb(t[k * 2], t[k * 2 + 1]);
    }
    D query(int l, int r) {
        D L, R;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l&1) L = comb(L, t[l++]);
            if (r&1) R = comb(t[--r], R);
        }
        return comb(L, R);
    }
};
int main() {
    //freopen("grass.in", "r", stdin);
    //freopen("grass.out", "w", stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N, M, K, Q;
    cin >> N >> M >> K >> Q;
    vector<vector<pair<int, int>>> adj(N);
    {
        vector<pair<int, pair<int, int>>> e(M);
        for(int i = 0; i < M; i++) {
            cin >> e[i].second.first >> e[i].second.second >> e[i].first;
        }
        sort(e.begin(), e.end());
        vector<int> p(N, -1);
        function<int(int)> get = [&] (int x) {
            return p[x] < 0 ? x : p[x] = get(p[x]);
        };
        for(auto [u, v] : e) {
            v.first--, v.second--;
            int a = get(v.first), b = get(v.second);
            if(a == b) continue;
            if(p[a] > p[b]) swap(a, b);
            p[a] += p[b], p[b] = a;
            adj[v.first].push_back({v.second, u});
            adj[v.second].push_back({v.first, u});
        }
    }

    vector<int> c(N);
    for(int i = 0; i < N; i++) cin >> c[i];

    vector<pair<int, int>> p(N);
    vector<SegT> segt(N, SegT(0));
    vector<int> ind(N);
    multiset<int> st;
    auto query = [&] (int s) {
        D cur = segt[s].query(0, segt[s].n - 1);
        if(cur.best.first == c[s]) {
            return cur.best2.second;
        } else {
            return cur.best.second;
        }
    };
    function<void(int, int)> dfs = [&] (int s, int e) {
        int cnt = 0;
        for(auto [u, v] : adj[s]) {
            if(u != e) {
                ind[u] = cnt++;
                p[u] = {s, v};
                dfs(u, s);
            }
        }
        segt[s] = SegT(cnt);
        if(cnt > 0) {
            for(auto [u, v] : adj[s]) {
                if(u != e) {
                    segt[s].mod(ind[u], c[u], v);
                }
            }
            st.insert(query(s));
        }
    };
    dfs(0, -1);
    for(int i = 0; i < Q; i++) {
        int A, B; cin >> A >> B;
        A--;

        if(A != 0) {
            st.erase(st.find(query(p[A].first)));
            segt[p[A].first].mod(ind[A], B, p[A].second);
            st.insert(query(p[A].first));
        }

        if(segt[A].n != 0) {
            st.erase(st.find(query(A)));
        }
        c[A] = B;
        if(segt[A].n != 0) {
            st.insert(query(A));
        }
        cout << *st.begin() << endl;
    }
}