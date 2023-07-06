#include <cplib/hash.h>
using namespace std;
const int MOD = 998244353;

void testcase() {
    int n, k; rd(n), rd(k);
    vector<Hash> d(n + 1, 1);
    for(int i = 0; i < k; i++) {
        int l, r; rd(l), rd(r);
        d[l - 1] *= 999 + i;
        d[r] /= 999 + i;
    }
    map<Hash, int> cnt;
    Hash h = 1;
    for(int i = 0; i < n; i++) {
        h *= d[i];
        cnt[h]++;
    }
    Comb<MOD> comb(n);
    mint<MOD> ans = 1;
    for(auto [u, v] : cnt) {
        if(v % 2 == 1) {
            cout << 0 << endl;
            return;
        }
        ans *= comb.choose(v, v / 2) / mint<MOD>(v / 2 + 1);
    }
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}