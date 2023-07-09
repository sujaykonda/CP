#include <cplib/general.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void tc() {
    int k; rd(k);
    vector<ll> g(1 + (1 << (k + 1)));
    map<ll, int> mp;
    for(int i = 1; i <= 1 << (k + 1); i++) {
        ll x; rd(x);
        g[i] = g[i - 1] ^ x;
        mp[g[i]] = i;
    }
    while(true) {
        int a = uniform_int_distribution<int>(0, g.size() - 3)(rng);
        int b = uniform_int_distribution<int>(a + 1, g.size() - 2)(rng);
        int c = uniform_int_distribution<int>(b, g.size() - 2)(rng);
        if(mp.find(g[a] ^ g[b] ^ g[c]) != mp.end()) {
            int d = mp[g[a] ^ g[b] ^ g[c]];
            if(d <= c) continue;
            cout << a + 1 << " " << b << " " << c + 1 << " " << d << endl;
            return;
        }
    }
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}