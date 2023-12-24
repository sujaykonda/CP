#include <bits/stdc++.h>
using namespace std;
const int MX = 1e6 + 1;
using ll = long long;

ll bsmax(ll lo, ll hi, function<bool(ll)> f)
{
    lo--;
    while (hi > lo)
    {
        ll mid = (hi + lo + 1) / 2;
        if (f(mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N; cin >> N;
    vector<int> cnt(MX);
    for(int i = 0; i < N; i++) {
        int x; cin >> x;
        cnt[x]++;
    }
    vector<ll> p(MX);
    for(int i = 0; i < MX - 1; i++) {
        p[i + 1] = p[i] + cnt[i];
    }
    vector<ll> d1(MX), d2(MX), smd1(MX), smd2(MX);
    for(int i = 1; i < MX; i++) {
        d1[i] = p[i];
        smd1[i] = smd1[i - 1] + d1[i];
    }
    for(int i = 1; i < MX; i++) {
        d2[i] = N - p[MX - i];
        smd2[i] = smd2[i - 1] + d2[i];
    }
    int Q; cin >> Q;
    for(int i = 0; i < Q; i++) {
        int a, b; cin >> a >> b;
        int j = bsmax(1, MX - 1, [&] (int x) {
            return (ll) a * d1[x] < (ll) b * d2[MX - x];
        });
        ll first = (ll) a * smd1[j] + (ll) b * smd2[MX - j - 1];
        cout << first << endl;
    }
}