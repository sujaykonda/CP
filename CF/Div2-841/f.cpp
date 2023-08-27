#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/math/mint.h>
using namespace std;
const int MOD = 998244353;

vector<mint<MOD>> mult;

mint<MOD> inter(vector<mint<MOD>>& ys) {
    mint<MOD> result = 0;
    int n = ys.size();
    for (int i = 0; i < n; i++) {
        result += ys[i] * mult[i];
    }
    return result;
}

int main() {
    int n, m; rd(n, m);
    mult.resize(n + 2, 1);
    for(int i = 0; i < mult.size(); i++) {
        for (int j = 0; j < mult.size(); j++) {
            if (j != i) {
                mult[i] *= mint<MOD>(m - j) / mint<MOD>(i - j);
            }
        }
    }
    Comb<MOD> comb(n);
    mint<MOD> ans;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            for(int k = j + 1; k <= n - i; k++) {
                mint<MOD> term = comb.choose(i - 1, j) * comb.choose(n - i, k);
                vector<mint<MOD>> ys(n + 2);
                for(int x = 0; x <= n; x++) {
                    ys[x + 1] = ys[x] + mint<MOD>(x + 1) * bpow(mint<MOD>(x), j) * bpow(mint<MOD>(x + 1), (n - i - k)) * bpow(mint<MOD>(m - 1 - x), k) * bpow(mint<MOD>(m - x), (i - 1 - j));
                }
                term *= inter(ys);
                ans += term;
            }
        }
    }
    cout << ans << endl;
}