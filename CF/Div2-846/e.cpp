#include <cplib/general.h>
using namespace std;

void tc() {
    int l; ll r; rd(l, r);
    vector<int> imp;
    int i;
    for(i = 1; i * i < l; i++) {
        imp.pb(i);
        imp.pb((l + i - 1) / i);
    }
    imp.pb(i);
    sort(imp.begin(), imp.end());
    ll ans = 0;
    ll mn = r / 2;
    for(int x : imp) {
        if(min(mn, r / (x + 1)) >= (l + x - 1) / x)
            ans += min(mn, r / (x + 1)) - (l + x - 1) / x + 1, mn = (l + x - 1) / x - 1;
    }
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}