#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = long long;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;

void fastio() { ios::sync_with_stdio(false), cin.tie(nullptr); }
istream& operator>>(istream& is, vi& a) { for(ll& v : a) is >> v; return is; }
ostream& operator<<(ostream& os, vi& a) { for(ll v : a) os << v << " "; return os; }
vi& operator--(vi& a) { for(ll& v : a) v--; return a;}
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

const ll inf = 1000000000000000;

void testcase() {
    int n, k;
    cin >> n >> k;
    vi a(n);
    cin >> a;
    vi cold(k), hot(k);
    cin >> cold >> hot;
    vi dp(k + 1, inf);
    multiset<ll> ms;
    vi base(n);
    dp[0] = 0;
    base[0] = cold[a[0] - 1];
    for(ll v : dp) ms.insert(v);
    for(int i = 1; i < n; i++) {
        if(a[i] == a[i - 1]) base[i] = base[i - 1] + hot[a[i] - 1];
        else base[i] = base[i - 1] + cold[a[i] - 1];
        ll mn = *ms.begin();
        if(dp[a[i - 1]] + base[i] > mn + base[i - 1] + cold[a[i] - 1]) {
            ms.erase(ms.find(dp[a[i - 1]]));
            dp[a[i - 1]] = mn + base[i - 1] + cold[a[i] - 1] - base[i];
            ms.insert(dp[a[i - 1]]);
        }
        if(dp[a[i - 1]] + base[i] > dp[a[i]] + base[i - 1] + hot[a[i] - 1]) {
            ms.erase(ms.find(dp[a[i - 1]]));
            dp[a[i - 1]] = dp[a[i]] + base[i - 1] + hot[a[i] - 1] - base[i];
            ms.insert(dp[a[i - 1]]);
        }
    }
    ll mn = *ms.begin() + base[n - 1];
    cout << mn << endl;
}

int main() {
    fastio();
    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
        testcase();
}