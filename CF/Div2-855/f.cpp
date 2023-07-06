#include <bits/stdc++.h>
using namespace std;
#define pb push_back
using ll = long long;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;


void fastio() { ios::sync_with_stdio(false), cin.tie(nullptr); }
istream& operator>>(istream& is, vi& v) { for(ll& i : v) is >> i; return is; }
ostream& operator<<(ostream& os, vi& v) { for(ll i : v) os << i << " "; return os; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }

const ll all = 0b11111111111111111111111111;

int main() {
    fastio();
    int n;
    cin >> n;
    vector<string> s(n);
    for(int i = 0; i < n; i++) cin >> s[i];
    map<ll, ll> mp;
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        array<ll, 26> cnt {};
        for(int j = 0; j < s[i].length(); j++)
            cnt[s[i][j] - 'a']++;
        ll parity = 0;
        for(int j = 0; j < 26; j++)
            parity += ((cnt[j] % 2) << j);
        for(int j = 0; j < 26; j++)
            if(cnt[j] == 0)
               mp[parity * 26 + j]++;
        for(int j = 0; j < 26; j++) {
            if(cnt[j] == 0) {
                ll nparity = all ^ (1 << j) ^ parity;
                ans += mp[nparity * 26 + j];
            }
        }
    }
    cout << ans << endl;
}