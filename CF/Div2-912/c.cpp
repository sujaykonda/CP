#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    vector<ll> suff(n + 1);
    for(ll i = n - 1; i >= 0; i--) suff[i] = a[i] + suff[i + 1];
    ll ans = suff[0];
    for(int i = 1; i < n; i++) if(suff[i] > 0) ans += suff[i];
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}