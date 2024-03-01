#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
using ll = long long;
int bpow(int a, ll p) { assert(p >= 0); return p == 0 ? 1 : (((ll)bpow(((ll)a * a) % MOD, p / 2) * (p & 1 ? a : 1)) % MOD); }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int D; cin >> D;
    set<pair<ll, ll>> dem; 
    auto should_erase = [&] (ll m, ll b, ll ma, ll ba) {
        return ((ba / ma) * m + min(m, ba % ma)) >= b;
    };
    while(D--) {
        ll m, b; cin >> m >> b;
        bool add = true;
        if(dem.upper_bound({m, b}) != dem.end()) {
            auto [ma, ba] = *dem.upper_bound({m, b});
            add = !should_erase(m, b, ma, ba);
        }
        if(add) {
            auto [p, _] = dem.insert({m, b});
            if(p != dem.begin()) {
                p--;
                while(should_erase((*p).first, (*p).second, m, b)) {
                    p = dem.erase(p);
                    if(p == dem.begin()) break;
                    p--;
                }
            }
        }
    }

}