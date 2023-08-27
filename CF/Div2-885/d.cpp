#include <cplib/general.h>
using namespace std;

void tc() {
    ll s, k; rd(s, k);
    ll best = (ll)s * k;
    if((s % 10) == 0 || (s % 10) == 5) {
        best = max(best, (s + (s % 10)) * (k - 1));
    } else {
        if(s % 10 % 2) s += s % 10, k--;
        for(int i = 0; i < 4; i++) {
            ll x1 = max((5 * k - s) / 40, 0ll);
            ll x2 = max((5 * k - s + 39) / 40, 0ll);
            best = max({best, (s + 20 * x1) * (k - 4 * x1), (s + 20 * x2) * (k - 4 * x2)});
            s += s % 10, k--;
            if(k < 0) break;
        }
    }
    cout << best << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}