#include <cplib/bs.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<pair<int, int>> ivs(n);
    for(int i = 0; i < n; i++) {
        int l, r, a, b;
        rd(l, r, a, b);
        ivs[i] = {l, b};
    }
    sort(ivs.begin(), ivs.end());
    vector<pair<int, int>> nivs;
    int mxr = 0;
    for(int i = 0; i < n; i++) {
        if(ivs[i].second > mxr) {
            nivs.pb(ivs[i]);
            mxr = ivs[i].second;
        }
    }
    ivs = nivs;
    n = ivs.size();
    vector<int> dp(n); dp[n - 1] = ivs[n - 1].second;
    for(int i = n - 2; i >= 0; i--) {
        if(ivs[i].second >= ivs[i + 1].first) {
            dp[i] = dp[i + 1];
        } else {
            dp[i] = ivs[i].second;
        }
    }
    int q; rd(q);
    for(int i = 0; i < q; i++) {
        int x; rd(x);
        int j = bsmax(0, n - 1, [&] (int j) { return ivs[j].first <= x; });
        if(j < 0) {
            cout << x << " ";
        } else {
            if(ivs[j].second < x) {
                cout << x << " ";
            } else {
                cout << dp[j] << " ";
            }
        }
    }
    cout << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}