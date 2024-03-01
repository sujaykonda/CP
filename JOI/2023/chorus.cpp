#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll m, b, s;
    ll eval(ll x) { return m * x + b; }
};
int main() {
    int N, K; cin >> N >> K;
    string s; cin >> s;
    vector<int> h(N);
    int x = 0, y = 0;
    for(int i = 0; i < 2 * N; i++) {
        if(s[i] == 'A') h[x] = y, x++;
        else y++;
    }
    auto f = [&] (ll k) {
        vector<pair<int, Line>> cht;
        int best = 0;
        vector<pair<ll, ll>> dp(N + 1);
        ll g = 0;
        int j = 0;
        for(int i = 0; i < N; i++) {
            while(j <= h[i] && j <= i) {
                Line l;
                l.m = -j;
                l.b = dp[j].first - g + (ll) i * j;
                while(cht.size() > 0) {
                    if(cht.back().second.eval(cht.back().second.s) > l.eval(cht.back().second.s)) cht.pop_back();
                    else break;
                    if(best == cht.size()) best--;
                }
                if(cht.size() == 0) {
                    l.s = 0;
                    cht.push_back({j, l});
                    best = 0;
                } else {
                    l.s = (l.b - cht.back().second.b) / (cht.back().second.m - l.m) + 1;
                    cht.push_back({j, l});
                }
                j++;
            }
            g += h[i];
            while(best + 1 < cht.size() && cht[best + 1].second.s <= i + 1) best++;
            dp[i + 1].first = cht[best].second.eval(i + 1) + k + g;
            dp[i + 1].second = dp[cht[best].first].second + 1;
        }
        return dp[N];
    };
    ll L = 0, R = (ll)N * N + 1;
    while(L < R) {
        ll mid = (L + R) / 2;
        if(f(mid).second <= K) {
            R = mid;
        } else {
            L = mid + 1;
        }
    }
    pair<ll, ll> ans = f(L);
    cout << ans.first - L * K << endl;
}