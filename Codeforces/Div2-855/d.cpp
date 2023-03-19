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


const array<ll, 3> M = {1000000007, 998919917, 1000000009};

ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m); }
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

void testcase() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    set<array<ll, 3>> hshs;
    vector<array<ll, 3>> P(n + 1);
    array<ll, 3> p {1, 1, 1};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < M.size(); j++) {
            P[i + 1][j] = (P[i][j] + (s[i] - 'a') * p[j]) % M[j];
            p[j] = (p[j] * 26) % M[j];
        }
    }
    for(int i = 1; i < n; i++) {
        array<ll, 3> hsh = P[i - 1];
        for(int j = 0; j < M.size(); j++) {
            hsh[j] = (hsh[j] + ((P[n][j] - P[i + 1][j] + M[j]) % M[j]) * minv(26 * 26, M[j])) % M[j];
        }
        hshs.insert(hsh);
    }
    cout << hshs.size() << endl;
}

int main() {
    fastio();

    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}