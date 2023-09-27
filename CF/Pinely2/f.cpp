#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<ll> a(n); rd(a);
    if(n == 1) {
        cout << 1 << endl;
        return;
    }
    vector<ll> pref(n + 1);
    for(int i = 0; i < n; i++) pref[i + 1] = pref[i] ^ a[i];
    vector<ll> left(n), right(n);
    left[0] = right[n - 1] = (pref[n] == 0 ? -1 : (1LL << lg(pref[n])));
    vector<int> dp(n);
    for(int s = n - 2; s >= 0; s--) {
        for(int l = 0; l + s < n; l++) {
            ll xr = pref[l + s + 1] ^ pref[l];
            bool good = left[l] == -1 || right[l + s] == -1 || (xr & left[l]) > 0 || (xr & right[l + s]) > 0;
            if(s == 0) dp[l] = good;
            if(good) {
                left[l] = xr == 0 ? -1 : (left[l] | (1LL << lg(xr)));
                right[l + s] = xr == 0 ? -1 : (right[l + s] | (1LL << lg(xr)));
            }
        }
    }
    
    for(int i = 0; i < n; i++) cout << dp[i];
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}