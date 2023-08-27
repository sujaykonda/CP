#include <cplib/math/mint.h>
using namespace std;

const int MXX = 1e9, MOD = 998244353;

int main() {
    int n; rd(n);
    vector<int> o(n), sm(n + 1);
    for(int i = 0; i < n; i++) {
        int t; rd(t);
        sm[i + 1] = sm[i];
        if(t == 1) {
            rd(o[i]);
        } else if(t == 2) {
            rd(o[i]); o[i] *= -1;
            sm[i + 1] = max(-MXX, sm[i + 1] + o[i]);
        } else {
            sm[i + 1] = max(-MXX, 2 * sm[i + 1]);
        }
    }
    vector<int> rep; int rsm = 0;
    mint<MOD> ans = 0, mult = 1;
    for(int i = n - 1; i >= 0; i--) {
        if(o[i] == 0) {
            if(sm[i] == 0) mult *= 2;
            else rep.pb(sm[i]);
        } else if(o[i] < 0) {
            rsm = max(-MXX, rsm + o[i]);
        } else {
            if(o[i] + rsm > 0) {
                int b = rep.size() - 1;
                int x = 0;
                while(x < rep.size() && o[i] + rsm + rep[b - x] > 0 ) x++;
                int cursm = 0, cur = 0;
                for(x--; x >= 0; x--) {
                    if(o[i] + rsm + rep[b - x] + cursm > 0) 
                        cursm += rep[b - x], cur += (1 << x);
                }
                ans += mult * mint<MOD>(cur + 1);
            }
        }
    }
    cout << ans << endl;
}
