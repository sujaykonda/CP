#include <cplib/ds/srq.h>
#include <cplib/bs.h>
using namespace std;

int _or(int a, int b) { return a | b; }

void tc() {
    int n, q; rd(n, q);
    vector<int> a(n); rd(a);
    int mx = 0;
    for(int i = 0; i < n; i++) mx |= a[i];
    vector<int> b(2 * n - 1);
    for(int i = 0; i < n - 1; i++)
        b[i] = b[n + i] = a[i] | a[i + 1];
    b[n - 1] = a[n - 1] | a[0];
    SRQ<int, _or> srq(b);
    vector<pair<int, ll>> imp;
    for(int i = 0; i < n; i++) imp.pb({-a[i], i});
    for(int i = n; i < 2 * n - 1; i++) {
        imp.pb({-b[i], i});
        int cur = b[i];
        while(cur != mx) {
            int j = bsmax(i - n + 1, i, [&] (ll x) { return srq.query(x, i) > cur; });
            cur = srq.query(j, i);
            imp.pb({-cur, i + (ll)(i - j) * (n - 1)});
        }
    }
    sort(imp.begin(), imp.end());
    map<int, ll> mp;
    ll mn = 1e18;
    for(int i = 0; i < imp.size(); i++) {
        if(imp[i].second < mn) {
            mp[-imp[i].first] = imp[i].second;
            mn = imp[i].second;
        }
    }
    for(int i = 0; i < q; i++) {
        int x; rd(x);
        if(x >= mx) {
            cout << -1 << endl;
        } else {
            cout << (*mp.lower_bound(x + 1)).second + 1 << endl;
        }
    }
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}