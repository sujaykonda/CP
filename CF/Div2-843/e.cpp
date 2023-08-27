#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<ll> a(n); rd(a);
    ll cur = 0, mn = 0, mx = 0;
    for(int ai : a) {
        cur += ai;
        mn = min(mn, cur);
        mx = max(mx, cur);
    }
    cout << mx - mn << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}