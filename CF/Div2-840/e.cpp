#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;

template<class T> void upd(T& a, T b) { a = min(a, b); }

int main() {
    int p; rd(p);

    vector<pair<int, int>> dp(p + 1, {2 * p, 0}); dp[0] = {0, 0};
    for(int i = 1; (i * (i - 1)) / 2 <= p; i++) {
        for(int j = 0; j <= p - (i * (i - 1)) / 2; j++) {
            upd(dp[j + (i * (i - 1)) / 2], {dp[j].first + i, dp[j].second - dp[j].first * i});
        }
    }
    cout << dp[p].first << " " << -dp[p].second << endl;
}