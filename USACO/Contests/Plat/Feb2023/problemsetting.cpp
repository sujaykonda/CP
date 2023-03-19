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

const ll MOD = 1000000007;

int main() {
    setio();
    int N, M;
    cin >> N >> M;
    vi bitmasks(N);
    for(int i = 0; i < M; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < N; j++)
            bitmasks[j] += (s[j] == 'H') << i;
    }
    vi cnt(1 << M);
    for(int mask in bitmasks) cnt[mask]++;
    vector<vi> dp(1 << M, vi(M));
    for(int mask = 0; mask < (1 << M); mask++) {
        ll poss = 0;
        ll perm = 1;
        for(int i = cnt[mask]; i > 0; i--) {
            perm = (perm * i) % MOD;
            poss = (poss + perm) % MOD;
        }
        dp[mask][0] = poss;
        for(int i = 0; i < M; i++)
            if(getbit(mask, i)) 
                dp[mask][0] = (dp[mask][0] + poss * dp[mask ^ (1 << i)][i]) % MOD;
        for(int i = 0 ; i < M - 1; i++) {
            dp[mask][i + 1] = dp[mask][i];
            if(getbit(mask, i)) 
                dp[mask][i + 1] = (dp[mask][i + 1] + dp[mask ^ (1 << i)][i]) % MOD;
        }
    }
    ll sum = 0;
    for(int mask = 0; mask < (1 << M); mask++)
        sum = (sum + dp[mask][0]) % MOD;
    cout << sum << endl;
}