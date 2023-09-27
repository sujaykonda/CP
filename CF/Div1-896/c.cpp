#include <cplib/math/mint.h>
using namespace std;

const int MOD = 998244353;

void tc() {
    ll n; int m; rd(n, m);
    int mxp = 2 * (lg(n) + 1) + 1;
    Comb<MOD> comb(m);
    vector<mint<MOD>> ev(mxp + 1);
    vector<mint<MOD>> cur(m + 1, 1);
    for(int i = 1; i <= mxp; i++) {
        for(int j = 0; j <= m; j++) {
            cur[j] *= j;
        }
        mint<MOD> invmi = 1; invmi /= cur[m];
        for(int j = 1; j <= m; j++) {
            ev[i] += j * (cur[j] - cur[j - 1]) * invmi; 
        }
    }
    map<ll, vector<mint<MOD>>> paths;
    map<ll, vector<mint<MOD>>> depths;
    paths[0] = {0};
    depths[0] = {0};
    paths[1] = {0, 1};
    depths[1] = {0, 1};
    function<void(ll)> f = [&] (ll x) {
        if(paths.count(x)) return;
        int flog = lg(x);
        ll base = (1LL << lg(x)) - 1;
        ll a = (base - 1) / 2 + min(x - base, (base + 1) / 2);
        ll b = (base - 1) / 2 + max(0LL, x - (base + 1) / 2 - base);
        f(a), f(b);
        vector<mint<MOD>> npaths(2 * depths[a].size());
        vector<mint<MOD>> ndepths(1 + paths[a].size());
        for(int i = 0; i < paths[a].size(); i++) {
            npaths[i] += paths[a][i];
        }
        for(int i = 0; i < paths[b].size(); i++) {
            npaths[i] += paths[b][i];
        }
        for(int i = 0; i < depths[a].size(); i++) {
            for(int j = 0; j < depths[b].size(); j++) {
                npaths[i + j + 1] += (depths[a][i] + (i == 0)) * (depths[b][j] + (j == 0));
            }
        }
        for(int i = 0; i < depths[a].size(); i++) {
            ndepths[i + 1] += depths[a][i];
        }
        for(int i = 0; i < depths[b].size(); i++) {
            ndepths[i + 1] += depths[b][i];
        }
        while(npaths.back().v == 0) npaths.pop_back();
        while(ndepths.back().v == 0) ndepths.pop_back();
        ndepths[1] += 1;
        paths[x] = npaths;
        depths[x] = ndepths;
    };
    f(n);
    mint<MOD> e;
    for(int i = 0; i < paths[n].size(); i++) e += ev[i] * paths[n][i];
    e *= bpow(mint<MOD>(m), n);
    cout << e.v << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}