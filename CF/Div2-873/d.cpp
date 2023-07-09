#include <cplib/ds/srq.h>
#include <cplib/bs.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<int> a(n); rd(a); a.pb(0);
    SRQ<int, _max<int>> srq(a);
    stack<pair<int, int>> s; s.push({n, 0});
    ll ans = 0;
    for(int i = 1; i < n; i++) ans += (ll) (n - i) * i;
    for(int i = n - 1; i >= 0; i--) {
        while(a[i] < a[s.top().first]) {
            int j = bsmin(0, i, [&] (ll x) { return srq.query(x, i) < a[s.top().first]; } );
            ans -= (ll)(i - j + 1) * (s.top().second - s.top().first);
            s.pop();
        }
        s.push({i, s.top().first});
    }
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}