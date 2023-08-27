#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;
const int SZ = 2e5 / 64, D = 80;
int lb(ll x) { return lg(x&-x) + 1; }
struct f_bitset {
    array<ll, SZ> a{};
    void insert(int x) {
        a[x / 64] ^= 1LL << (x % 64);
    }
    friend int common(f_bitset& a, f_bitset& b) {
        for(int i = 0; i < SZ; i++) {
            if(a.a[i] != b.a[i]) {
                return lb(a.a[i] ^ b.a[i]) + i * 64;
            }
        }
        return 0;
    }
};

int main() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    map<int, vector<int>> mp;
    for(int i = 0; i < n; i++) mp[a[i]].pb(i);
    vector<int> rev;
    for(auto& [u, v] : mp) {
        for(int i : v) a[i] = rev.size();
        rev.pb(u);
    }
    vector<f_bitset> lbs(n / D + 1);
    f_bitset bs;
    lbs[0] = bs;
    for(int i = 1; i <= n; i++) {
        bs.insert(a[i - 1]);
        if(i % D == 0) {
            lbs[i / D] = bs;
        }
    }
    vector<f_bitset> rbs = lbs;

    int q; rd(q);
    int last = 0;
    for(int i = 0; i < q; i++) {
        int l, r; rd(l, r);
        l ^= last; l--;
        r ^= last;
        auto insert = [&] (f_bitset& bs, int x) {
            for(int j = x - (x % D) + 1; j <= x; j++) {
                bs.insert(a[j - 1]);
            }
        };
        insert(lbs[l / D], l);
        insert(rbs[r / D], r);
        last = common(lbs[l / D], rbs[r / D]) - 1;
        if(last < 0) last = 0;
        else last = rev[last];
        insert(lbs[l / D], l);
        insert(rbs[r / D], r);
        cout << last << endl;
    }
}