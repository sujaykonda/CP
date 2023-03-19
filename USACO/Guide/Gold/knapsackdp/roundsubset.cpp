#include <bits/stdc++.h>
using namespace std;
using ll = long long;



int main() {
    int n, k;
    cin >> n >> k;
    vector<pair<ll, ll>> f(n);
    for(int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        ll p = 1;
        while(a % (5 * p) == 0) p *= 5, f[i].first++;
        p = 1;
        while(a % (2 * p) == 0) p *= 2, f[i].second++;
    }
    vector<vector<ll>> prevdp(k + 1, vector<ll>(7201, -1));
    vector<vector<ll>> curdp(k + 1, vector<ll>(7201, -1));
    prevdp[k][0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= k; j++) {
            for(int m = 0; m < 7201; m++) {
                if(prevdp[j][m] != -1) {
                    curdp[j][m] = max(curdp[j][m], prevdp[j][m]);
                    if(j > 0)
                        curdp[j - 1][m + f[i].first] = max(curdp[j - 1][m + f[i].first], prevdp[j][m] + f[i].second);
                }
            }
        }
        prevdp = curdp;
    }
    ll mx = 0;
    for(ll i = 0; i < 7201; i++) {
        mx = max(mx, min(i, curdp[0][i]));
    }
    cout << mx << endl;
}