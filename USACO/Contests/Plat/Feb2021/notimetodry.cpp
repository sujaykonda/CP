#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
};

int main() {
    int N, Q; cin >> N >> Q;
    vector<int> c(N + 1);
    for(int i = 1; i <= N; i++) cin >> c[i];
    vector<int> ans(Q);
    vector<vector<pair<int, int>>> q(N + 1);
    for(int i = 0; i < Q; i++) {
        int a, b; cin >> a >> b;
        b, a--;
        q[b].push_back({a, i});
    }
    BIT bit(N);
    stack<int> s; s.push(-1);
    for(int i = 1; i <= N; i++) {
        bit.add(i, 1);
        while(s.top() != -1 && c[s.top()] > c[i]) {
            s.pop();
        }
        if(s.top() != -1 && c[s.top()] == c[i]) {
            bit.add(s.top(), -1);
        }
        s.push(i);
        for(auto [u, v] : q[i]) ans[v] = bit.sum(i) - bit.sum(u);
    }
    for(int ai : ans) cout << ai << endl;

}