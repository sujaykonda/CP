#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define s second
using ll = long long;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;


void fastio() { ios::sync_with_stdio(false), cin.tie(nullptr); }
istream& operator>>(istream& is, vi& v) { for(ll& i : v) is >> i; return is; }
ostream& operator<<(ostream& os, vi& v) { for(ll i : v) os << i << " "; return os; }
istream& operator>>(istream& is, pi& p) { return is >> p.first >> p.second; }
ostream& operator<<(ostream& os, pi& p) { return os << p.first << " " << p.second; }


void testcase() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    array<char, 4> c{'m', 'e', 'o', 'w'};
    int i = 0, j = 0;
    while(i < n) {
        if(j == 4 || tolower(s[i]) != c[j]) {
            cout << "NO\n";
            return;
        }
        while(i < n && tolower(s[i]) == c[j]) i++;
        j++;
    }
    if(j == 4)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    fastio();
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) testcase();
}