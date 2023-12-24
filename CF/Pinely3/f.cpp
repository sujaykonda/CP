#include <cplib/math/mint.h>
using namespace std;

const int MOD = 998244353;

void tc() {
    
    int n; rd(n);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) rd(a[i]);
    if(a[n] == -1) a[n] = n;
    if(a[n] != n) {
        cout << 0 << endl;
        return;
    }
    mint<MOD> ans = 1;
    Comb<MOD> comb(n);

    auto solve = [&] (int l, int r, int c) {
        mint<MOD> v = 0;
        for(int i = 0; i <= r - l; i++) {
            v += comb.choose(l, i) * comb.perm(r - l, i) * comb.choose(r - i, c - i) * comb.perm(r - l, c - i); 
        }
        return v;
    };
    int last = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] != -1) {
            ans *= solve(last - a[last], i - a[last], a[i] - a[last]);
            last = i;
        }
    }
    cout << ans.v << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}