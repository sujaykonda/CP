#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll g = 0;
struct Quad {
    ll a, b, c, l, r;
    ll eval(ll x) { return (a + g) * (x * x) + b * x + c; }
    ll findmin(ll d) {
        return min(r, max(l, (d - b) / (2 * (a + g)) + ((d - b) % (2 * (a + g)) >= (a + g))));
    }
};

int main() {
    int N, M; cin >> N >> M;
    vector<ll> c(M);
    for(int i = 0; i < M; i++) cin >> c[i];
    int Q; cin >> Q;
    vector<vector<pair<int, int>>> q(M);
    for(int i = 0; i < Q; i++) {
        int a, b; cin >> a >> b;
        q[--b].push_back({a, i});
    }

    vector<ll> ans(Q);

    vector<Quad> quads;
    quads.push_back(Quad{0, c[0], -c[0], 1, N});
    auto answer = [&] (vector<pair<int, int>> q) {
        for(auto [u, v] : q) {
            int l = -1, r = quads.size() - 1;
            while(l < r) {
                int m = (l + r + 1) / 2;
                if(quads[m].l <= u) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            ans[v] = quads[l].eval(u);
        }
    };
    answer(q[0]);
    for(int i = 1; i < M; i++) {
        g++;
        Quad prev = quads.back();
        quads.pop_back();
        while(quads.size() > 0) {
            ll mn1 = quads.back().findmin(c[i]);
            ll mn2 = prev.findmin(c[i]);
            if(quads.back().eval(mn1) - mn1 * c[i] > prev.eval(mn2) - mn2 * c[i]) {
                break;
            }
            prev = quads.back();
            quads.pop_back();
        }
        quads.push_back(prev);
        ll mn = quads.back().findmin(c[i]);
        ll mnv = quads.back().eval(mn);
        if(quads.back().l == mn) {
            quads.pop_back();
        } else {
            quads.back().r = mn - 1;
        }
        quads.push_back(Quad({-g, c[i], mnv - (mn * c[i]), mn, N}));
        answer(q[i]);
    }
    for(ll ai : ans) cout << ai << '\n';
}