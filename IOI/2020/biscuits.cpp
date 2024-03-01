#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MXK = 60;

ll count_tastiness(ll x, vector<ll> a) {
    a.resize(MXK, 0);
    vector<ll> f(MXK + 1);
    f[0] = 1;
    for(int i = 0; i < MXK; i++) {
        ll sm = 0;
        ll prev = 0;
        ll mx = 0;
        for(int j = i; j >= 0; j--) {
            // f[j] to f[i] transition
            sm += a[j] * (1LL << j);
            mx ^= 1LL << (i - j);
            ll nw = min((sm / x) >> j, mx);
            f[i + 1] += f[j] * max(0ll, nw + 1 - prev);
            prev = 2ll * max(prev, nw + 1);
        }
    }
    return f[MXK];
}

int main() {
    cout << count_tastiness(1ll, {931452265312067782ll}) << endl;
}