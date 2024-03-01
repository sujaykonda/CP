#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void tc() {
    int n, b, x; cin >> n >> b >> x;
    vector<int> c(n);
    int mxc = 0;
    for(int i = 0; i < n; i++) cin >> c[i], mxc = max(mxc, c[i]);
    vector<ll> v(mxc+1);
    sort(c.begin(), c.end());
    int prev = 0;
    for(int i : c) {
        int prevv = v[prev];
        for(int j = 1; j <= i; j++) {
            if(j > prev) v[j] += prevv;
            v[j] += (ll)(j - (i % j)) * (i / j) * (i - (i / j));
            v[j] += (ll)((i % j)) * (i / j + 1) * (i - (i / j) - 1);
        }
        prev = i;
    }
    ll best = 0;
    for(int i = 1; i <= mxc; i++) best = max(best, (ll)b * v[i] / 2 - (ll)(i - 1) * x);
    cout << best << endl;
}

int main() {
    int t; cin >> t;
    while(t--) tc();
}