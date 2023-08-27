#include <cplib/math/mint.h>
using namespace std;
const int MOD = 998244353;
const int MAXJMP = 59;
struct f {
    vector<mint<MOD>> c;
    mint<MOD> v = 0;
    f& operator*=(mint<MOD> x) {
        this->v *= x; for(mint<MOD>& i : this->c) i *= x;
        return *this; }
};

int main() {
    // fs is a list of functions that allow you to skip multiple steps of dp by powers of two (similar to binary jumping)
    vector<f> fs;
    fs.pb(f{{(MOD + 1) / 2, (MOD + 1) / 2}, 1});
    for(int i = 0; i < MAXJMP; i++) {
        f cur; cur.c.resize(i + 3); cur.v = fs[i].v;
        for(int j = 0; j <= i; j++) {
            f nw = fs[i - j]; nw *= fs[i].c[j];
            for(int k = j; k <= i + 1; k++) {
                cur.c[k] += nw.c[k - j];
            }
            cur.v += nw.v;
        }
        f nw = fs[0]; nw *= fs[i].c[i + 1];
        for(int k = i + 1; k <= i + 2; k++) {
            cur.c[k] += nw.c[k - i - 1];
        }
        cur.v += nw.v;
        fs.pb(cur);
    }
    map<ll, mint<MOD>> mp; mp[0] = 0;
    function<mint<MOD>(ll)> solve = [&] (ll x) {
        if(mp.find(x) != mp.end()) return mp[x];
        int hb = lg(x&-x);
        mint<MOD> ans = fs[hb].v;
        for(int i = 0; i <= hb + 1; i++) {
            ans += fs[hb].c[i] * solve((x - (1LL << hb) + (1LL << i) - 1) / (1LL << i));
        }
        mp[x] = ans;
        return ans;
    };
    int t; rd(t);
    while(t--) {
       ll n; rd(n);
       cout << solve(n - 1).v << endl;;
    }
}