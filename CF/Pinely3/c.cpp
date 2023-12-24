#include <cplib/general.h>
using namespace std;

int main() {
    int t; rd(t);
    while(t--) {
        int n; cin >> n;
        vector<int> l(n), r(n), c(n); rd(l, r, c);
        vector<pair<int, int>> lr;
        for(int li : l) lr.push_back({li, 0});
        for(int ri : r) lr.push_back({ri, 1});
        sort(lr.begin(), lr.end());
        vector<ll> sz;
        stack<int> s;
        for(auto [u, v] : lr) {
            if(v == 0) {
                s.push(u);
            } else {
                sz.push_back(u - s.top());
                s.pop();
            }
        }
        sort(c.begin(), c.end(), greater<int>());
        sort(sz.begin(), sz.end());
        ll ans = 0;
        for(int i = 0; i < n; i++) ans += (ll) sz[i] * c[i];
        cout << ans << endl;
    }
}