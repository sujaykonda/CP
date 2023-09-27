#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
    int N; cin >> N;
    vector<int> a(2 * N);
    for(int i = 0; i < 2 * N; i++) {
        cin >> a[i];
    }
    int ones = 0;
    for(int i = 0; i < 2 * N; i++) ones += a[i];
    ll ans = (ll) N * N;
    int m = 1;
    int mult = 1;
    auto solve = [&] () {
        auto calc_inv = [&] (int l, int r) {
            ll inv = 0;
            int csm = 0;
            for(int i = l; i < r; i++) {
                if(a[i] == 0) {
                    inv += csm;
                }
                csm += a[i];
            }
            return inv;
        };
        ll delta = calc_inv(0, N) - calc_inv(N, 2 * N);
        ans = min(ans, llabs(delta));
        int addedcnt = 0;
        ll addedsm = 0;
        ll sm = 0;
        int cnt = 0;
        for(int i = N - 1; i >= 0; i--) {
            if(a[i] == m) {
                while(cnt + addedcnt < N && a[N + cnt + addedcnt] == m) {
                    addedsm += N + cnt + addedcnt;
                    addedcnt++;
                }
                sm += i;
                cnt++;
                if(cnt + addedcnt > N) break;
                ll deltaincrease = (ll) (ones - N) * cnt - ((ll) (N - 1) * cnt - sm) + ((ll)cnt * (cnt - 1)) / 2 + (ll) (N + cnt) * addedcnt - addedsm + ((ll)addedcnt * (addedcnt - 1)) / 2;
                ll swaps = (ll) N * cnt - sm + ((ll)cnt * (cnt - 1)) / 2 + (ll) (N + cnt) * addedcnt - addedsm + ((ll)addedcnt * (addedcnt - 1)) / 2;
                ans = min(ans, llabs(delta + mult * deltaincrease) + swaps);
            }
        }
    };
    solve();
    m = 0;
    mult = -1;
    solve();
    cout << ans << endl;
}