#include <cplib/ds/bit.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> p(n), q(k); rd(p, q);
    vector<BIT> pbits(20, BIT(n));
    vector<array<ll, 3>> e;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 20; j++) {
            e.push_back({(ll)p[i] * (1 << j), i, j});
        }
    }
    sort(e.begin(), e.end());
    reverse(e.begin(), e.end());
    ll ans = 0;
    for(auto [u, v, w] : e) {
        for(int i = 0; i < 20; i++) {
            if(w == 0 || i == 0) {
                ans += pbits[i].sum(v) * max(0ll, k - max(w, (ll)i));
                ans %= 998244353;
                if(i == 19 && i < k) ans += pbits[i].sum(v) * (ll)(k - 19) * (k - 20) / 2;
            }
        }
        pbits[w].add(v + 1, 1);
    }
    ll qinv = 0;
    BIT qbit(k);
    vector<int> rq(k);
    for(int i = 0; i < k; i++) rq[q[i]] = i;
    for(int i = k - 1; i >= 0; i--) {
        qinv += qbit.sum(rq[i] + 1);
        qbit.add(rq[i] + 1, 1);
    }
    ans += n * qinv;
    ans %= 998244353;
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}