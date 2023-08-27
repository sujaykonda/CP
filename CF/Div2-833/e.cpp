#include <cplib/bs.h>
#include <cplib/ds/srq.h>
#include <cplib/math/mint.h>
using namespace std;
const int MOD = 1e9 + 7;
int _max(int a, int b) { return max(a, b); }

void tc() {
    int n, m; rd(n, m);
    vector<int> a(n); rd(a);
    SRQ<int, _max> srq(a);
    auto f = [&] (int l, int r) {
        int mn = srq.query(l, r);
        return bsmin(l, r, [&] (int x) { return srq.query(l, x) == mn; });
    };
    function<vector<mint<MOD>>(int l, int r)> dc = [&] (int l, int r) {
        int mx = f(l, r);
        vector<mint<MOD>> ans(m + 1, 1); ans[0] = 0;
        if(l < mx) {
            vector<mint<MOD>> left = dc(l, mx - 1);
            for(int i = 1; i <= m; i++) {
                ans[i] *= left[i - 1];
            }
        }
        if(mx < r) {
            vector<mint<MOD>> right = dc(mx + 1, r);
            for(int i = 1; i <= m; i++) {
                ans[i] *= right[i];
            }
        }
        for(int i = 1; i <= m; i++) ans[i] += ans[i - 1];
        return ans;     
    };
    cout << dc(0, n - 1)[m] << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}