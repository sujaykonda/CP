#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = int;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;

void fastio() { ios::sync_with_stdio(false), cin.tie(nullptr); }
istream& operator>>(istream& is, vi& v) { for(ll& i : v) is >> i; return is; }
ostream& operator<<(ostream& os, vi& v) { for(ll i : v) os << i << " "; return os; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

void upd(int& a, int b) { a = max(a, b); }

int main() {
    freopen("subrev.in", "r", stdin);
    freopen("subrev.out", "w", stdout);
    fastio();
    int n;
    cin >> n;
    vi a(n);
    cin >> a;
    for(int i = 0; i < n; i++) a[i]--;
    vector<vector<array<array<int, 50>, 50>>> dp(n + 1, vector<array<array<int, 50>, 50>>(n));
    for(int i = 0; i < n; i++)
        dp[1][i][a[i]][a[i]] = 1;

    for(int s = 2; s <= n; s++) {
        for(int i = 0; i <= n - s; i++) {
            dp[s][i] = dp[s - 1][i];
            for(int l = 0; l < 50; l++) {
                for(int r = l; r < 50; r++) {
                    upd(dp[s][i][l][r], dp[s - 1][i + 1][l][r]);
                    if(l >= a[i])
                        upd(dp[s][i][a[i]][r], dp[s - 1][i + 1][l][r] + 1);
                    if(r <= a[i + s - 1])
                        upd(dp[s][i][l][a[i + s - 1]], dp[s - 1][i][l][r] + 1);
                    upd(dp[s][i][min(l, a[i + s - 1])][max(r, a[i])], (a[i + s - 1] <= l) + (r <= a[i]) + dp[s - 2][i + 1][l][r]);
                }
            }
        }
    }
    int mx = 0;
    for(int l = 0; l < 50; l++) {
        for(int r = l; r < 50; r++) {
            upd(mx, dp[n][0][l][r]);
        }
    }
    cout << mx << endl;
}