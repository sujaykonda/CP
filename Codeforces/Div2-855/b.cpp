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

void testcase() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<pair<int, int>> mp(26);
    for(int i = 0; i < n; i++)
        if(isupper(s[i]))
            mp[tolower(s[i]) - 'a'].first++;
        else
            mp[tolower(s[i]) - 'a'].second++;
    int pairs = 0;
    for(int i = 0; i < 26; i++)
        pairs += min(mp[i].first, mp[i].second);
    for(int i = 0; i < 26; i++) {
        while(k > 0 && mp[i].first >= 2 + mp[i].second) {
            mp[i].first--;
            mp[i].second++;
            pairs++;
            k--;
        }
        while(k > 0 && mp[i].first + 2 <= mp[i].second) {
            mp[i].first++;
            mp[i].second--;
            pairs++;
            k--;
        }
    }
    cout << pairs << endl;
}

int main() {
    fastio();
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}
