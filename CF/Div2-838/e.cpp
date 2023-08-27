#include <cplib/math/mint.h>
using namespace std;

const int MOD = 998244353;

int main() {
    int n; rd(n);
    if(n % 2 == 1) {
        cout << 0 << endl;
        return 0;
    }
    Comb<MOD> comb(n - 2);
    mint<MOD> ans = 0;
    for(int s = 1; s < n; s++) {
        ans += (s % 2 ? -1 : 1) * comb.choose(n - 2, s - 1) * bpow(mint<MOD>(n - s), n - s - 1) * bpow(mint<MOD>(s), s - 1);
    }
    cout << ans << endl;
}