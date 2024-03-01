#include <cplib/math/mint.h>
using namespace std;
const int MOD = 998244353;
int main() {
    int t; rd(t);

    map<ll, pair<mint<MOD>, mint<MOD>>> f;
    f[0] = {0, 0};
    f[1] = {1, 0};
    function<void(ll)> calc = [&] (ll sz) {
        if(f.count(sz)) return;
        ll lsz = (sz + 1) / 2;
        ll rsz = sz - (sz + 1) / 2;
        calc(lsz);
        pair<mint<MOD>, mint<MOD>> lf = f[lsz];
        calc(rsz);
        pair<mint<MOD>, mint<MOD>> rf = f[rsz];
        pair<mint<MOD>, mint<MOD>> cf;
        cf.first = 2 * lf.first + 2 * rf.first + (bpow(mint<MOD>(2), lsz) - 1) * (bpow(mint<MOD>(2), rsz) - 1);
        cf.second = lf.second + rf.second + rf.first;
        f[sz] = cf;
    };

    while(t--) {
        ll sz; rd(sz);
        calc(sz);
        cout << (f[sz].first + f[sz].second).v << endl;
    }
}