#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
};

struct SegT {
    vector<int> lz, mx;
    SegT(int n) { lz.resize(4 * n), mx.resize(4 * n); }
    int upd(int u, int l, int r, int s, int lb, int rb) {
        l = max(lb, l), r = min(rb, r);
        if(l > r) return 0;
        if(l == lb && rb == r) { int oldmx = mx[s]; lz[s] = u, mx[s] = u; return oldmx; }
        int m = (lb + rb) / 2;
        mx[2 * s + 1] = max(lz[s], mx[2 * s + 1]);
        lz[2 * s + 1] = max(lz[s], lz[2 * s + 1]);
        mx[2 * s] = max(lz[s], mx[2 * s]);
        lz[2 * s] = max(lz[s], lz[2 * s]);
        int res = max(upd(u, l, r, 2 * s, lb, m), upd(u, l, r, 2 * s + 1, m + 1, rb));
        mx[s] = max(mx[2 * s], mx[2 * s + 1]);
        return res;
    }
};

int main() {
    int N; cin >> N;
    vector<int> e(2 * N + 1);
    vector<pair<int, int>> iv(N + 1);
    for(int i = 1; i <= N; i++) {
        cin >> iv[i].second;
    }
    for(int i = 1; i <= N; i++) {
        cin >> iv[i].first;
    }
    vector<int> mxl(N + 1), mnr(N + 1);
    SegT segt(2 * N);
    for(int i = 1; i <= N; i++) {
        mxl[i] = segt.upd(i, iv[i].first, iv[i].second, 1, 1, 2 * N);
    }
    segt = SegT(2 * N);
    for(int i = N; i >= 1; i--) {
        mnr[i] = N + 1 - segt.upd(N + 1 - i, iv[i].first, iv[i].second, 1, 1, 2 * N);
    }

    int Q;
    cin >> Q;
    vector<vector<pair<int, int>>> q(N + 1);
    for(int i = 0; i < Q; i++) {
        int l, r; cin >> l >> r;
        q[r].push_back({l, i});
    }
    vector<int> ans(Q);
    BIT bit(N + 1);
    vector<vector<int>> rem(N + 2);
    for(int i = 1; i <= N; i++) {
        for(int u : rem[i]) {
            bit.add(mxl[u] + 1, -1);
            bit.add(u + 1, 1);
        }
        bit.add(mxl[i] + 1, 1);
        bit.add(i + 1, -1);
        rem[mnr[i]].push_back(i);
        for(auto [u, v] : q[i]) {
            ans[v] = bit.sum(u);
        }
    }
    for(int a : ans) {
        if(a == 0) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}