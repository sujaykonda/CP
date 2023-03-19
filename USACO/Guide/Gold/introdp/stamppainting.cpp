#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = long long;
typedef pair<ll, ll> pi;
typedef vector<ll> vi;
typedef vector<pi> vpi;

void setio(string name = "") { 
    ios::sync_with_stdio(false), cin.tie(nullptr); 
    if(name != "") {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
istream& operator>>(istream& is, vi& a) { for(ll& v : a) is >> v; return is; }
ostream& operator<<(ostream& os, vi& a) { for(ll v : a) os << v << " "; return os; }
vi& operator--(vi& a) { for(ll& v : a) v--; return a;}
vi range(int s, int e) { vi r(e - s); for(int i = s; i < e; i++) r[i - s] = i; return r; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

const ll MOD = 1000000007;
int main() {
    setio("spainting");
    int N, M, K;
    cin >> N >> M >> K;
    vi dp(N + 1);
    ll S = 1;
    dp[0] = 1;
    for(int i = 1; i < K; i++)
        dp[i] = (dp[i - 1] * M) % MOD, S = (S + dp[i]) % MOD;
    for(int i = K; i <= N; i++) {
        S = (S - dp[i - K] + MOD) % MOD;
        dp[i] = (S * (M - 1)) % MOD;
        S = (S + dp[i]) % MOD;
    }
    ll all = 1;
    for(int i = 1; i <= N; i++)
        all = (all * M) % MOD;
    cout << (all - dp[N] + MOD) % MOD << endl;
}