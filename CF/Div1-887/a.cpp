#include <cplib/general.h>
using namespace std;

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    if(a[0] != 1) {
        cout << 1 << endl;
        return;
    }
    ll ans = 1, days = 0;
    for(int i = 1; i < n; i++) {
        days += (ll)(a[i] - ans - 1) / i;
        ans += (ll)((a[i] - ans - 1) / i) * i;
        if(days > k) {
            ans -= (ll)(days - k) * i, days = k;
            break;
        }
    }
    if(days < k) ans += (ll)(k - days) * n;
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}