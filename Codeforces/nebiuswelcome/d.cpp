#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define in :
#define getbit(mask, i) ((mask & (1 << i)) > 0)
using ll = long long;
typedef pair<ll, ll> pi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

void setio(string name = "") { 
    ios::sync_with_stdio(false), cin.tie(nullptr); 
    if(name.length()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
istream& operator>>(istream& is, vi& a) { for(ll& v : a) is >> v; return is; }
ostream& operator<<(ostream& os, vi& a) { for(ll v : a) os << v << " "; return os; }
vi& operator--(vi& a) { for(ll& v : a) v--; return a;}
vi range(int s, int e) { vi r(e - s); for(int i = s; i < e; i++) r[i - s] = i; return r; }
vi range(int e) { return range(0, e); }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

ll n, m;
int mnfloor(string& floor) {
    int sum = 0;
    for(int i = 0; i < m; i++) 
        sum += floor[i] == '1';
    vi dp(m + 1);
    for(int i = 1; i < m; i++) {
        dp[i + 1] = dp[i];
        if(floor[i - 1] == '1' && floor[i] == '1')
            dp[i + 1] = max(dp[i + 1], 1 + dp[i - 1]);
    }
    return sum - min(m / 4, dp[m]);
}

int mxfloor(string& floor) {
    int sum = 0;
    for(int i = 0; i < m; i++) 
        sum += floor[i] == '1';
    vi dp(m + 1);
    for(int i = 1; i < m; i++) {
        dp[i + 1] = dp[i];
        if(floor[i - 1] == '0' || floor[i] == '0')
            dp[i + 1] = max(dp[i + 1], 1 + dp[i - 1]);
    }
    return sum + min(0ll, dp[m] - m / 4);
}

int main() {
    cin >> n >> m;
    ll mns = 0, mxs = 0;
    for(int i = 0; i < n; i++) {
        string floor;
        cin >> floor;
        mns += mnfloor(floor);
        mxs += mxfloor(floor);
    }
    cout << mns << " " << mxs << endl;
}